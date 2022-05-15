//
// Created by akb on 2022-05-14.
//

#ifndef HTTPRESPONSEPARSER_PARSER_H
#define HTTPRESPONSEPARSER_PARSER_H

#include<iostream>
#include<map>
#include<vector>
#include<string>
#include"parserhelpers.h"
#include"header.h"
using namespace std;

// Define a class with required attributes. We can use states to determine at which stage of parsing we are in
class responseParser
{
private:
    int responseCode;
    Version version;
    int validHeaders;
    int invalidHeaders;
    std::map<std::string, Header> headers;
    std::string error;

public:
    responseParser (int responseCode, Version version, int validHeaders, int invalidHeaders, std::map<std::string, Header> headers, std::string error) noexcept: responseCode(responseCode), version(version), validHeaders(validHeaders), invalidHeaders(invalidHeaders), headers(std::move(headers)), error(std::move(error))
    {
    }

    [[nodiscard]] int get_response_code() const noexcept
    {
        return this->responseCode;
    }

    [[nodiscard]]  string get_version() const noexcept
    {
        return version_to_string(this->version);
    }

    [[nodiscard]] int get_valid_headers() const noexcept
    {
        return this->validHeaders;
    }

    [[nodiscard]] int get_invalid_headers() const noexcept
    {
        return this->invalidHeaders;
    }

    [[nodiscard]] std::map<std::string, Header> get_headers() const noexcept
    {
        return this->headers;
    }

    [[nodiscard]]  string get_error() const noexcept
    {
        return this->error;
    }

    static responseParser parseHttpResponse(const std::string& response) noexcept
    {
        int valid_headers = 0;
        int invalid_headers = 0;
        std::map<std::string, Header> headers;
        std::string error;
        Version version = Version::HTTP_1_0;

        std::vector<std::string> segments = parserHelpers::split(response, std::string(HTTP::LINE_END) + std::string(HTTP::LINE_END));

        std::string headerSegment = segments[0];

        std::vector<std::string> headerLines = parserHelpers::split(headerSegment, std::string(HTTP::LINE_END));

        const std::string& responseCodeLine = headerLines[0];

        bool responseCheck = parserHelpers::validateStatusLine(responseCodeLine);
        if (!responseCheck)  {
            error="Invalid status line";
            return {0 , version, -1, -1, headers, error};
        }
        std::vector<std::string> responseCodeSegments = parserHelpers::split(responseCodeLine, " ");
        version = version_from_string(responseCodeSegments[1]);
        int responseCode = std::stoi(responseCodeSegments[1]);

        headerLines.erase(headerLines.begin());

        for (const std::string& line : headerLines)
        {
            if (line.find(':') == string::npos) {
                invalid_headers++;
                continue;
            }
            const Header header = Header::deserialize(line);
            bool headerCheck = parserHelpers::validateHeaderLine(line);
            if (headerCheck) {
                headers.insert(std::make_pair(header.get_key(), header));
                valid_headers++;
            } else {
                invalid_headers++;
            }
        }
        return {responseCode, version, valid_headers, invalid_headers, headers, error};
    }
};

std::ostream &operator<<(std::ostream &stream, const responseParser &resp)
{
    if (resp.get_error() != "") {
        stream << resp.get_error() << "\n";
        return stream;
    }
    stream << resp.get_version()<< "\n";
    stream << "Status:"<< resp.get_response_code()  << "\n";
    stream << "Number of valid headers:" << resp.get_valid_headers()<< "\n";
    stream << "Number of invalid headers:" << resp.get_invalid_headers()<< "\n";
    return stream;
}

#endif //HTTPRESPONSEPARSER_PARSER_H