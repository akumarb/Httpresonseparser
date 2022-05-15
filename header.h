//
// Created by akb on 2022-05-14.
//

#ifndef HTTPRESPONSEPARSER_HEADER_H
#define HTTPRESPONSEPARSER_HEADER_H

#include<string>
#include<iostream>
#include<vector>
#include"parserhelpers.h"

using namespace std;

enum class Version
{
    HTTP_1_0,
    HTTP_1_1,
    HTTP_2_0
};

namespace HTTP
{
    // For CR LF check
    constexpr static std::string_view LINE_END = "\r\n";
}

std::string to_string(Version version)
{
    switch(version)
    {
        case Version::HTTP_1_0:
            return "HTTP/1.0";

        case Version::HTTP_1_1:
            return "HTTP/1.1";

        case Version::HTTP_2_0:
            return "HTTP/2.0";
    }
}

std::string version_to_string(Version version)
{
    switch(version)
    {
        case Version::HTTP_1_0:
            return "HTTP Version:1.0";

        case Version::HTTP_1_1:
            return "HTTP Version:1.1";

        case Version::HTTP_2_0:
            return "HTTP Version 2.0";
    }
}

Version version_from_string (const std::string& version) noexcept
{
    if (version == to_string(Version::HTTP_1_0))
    {
        return Version::HTTP_1_0;
    }
    else if (version == to_string(Version::HTTP_1_1))
    {
        return Version::HTTP_1_1;
    }
    else if (version == to_string(Version::HTTP_2_0))
    {
        return Version::HTTP_2_0;
    }
    return Version::HTTP_1_0;
}

class Header
{
private:
    std::string key;
    std::string value;

public:
    Header ( std::string& key, std::string& value) noexcept: key(std::move(key)), value(std::move(value))
    {
    }

    [[nodiscard]] const std::string& get_key() const noexcept
    {
        return this->key;
    }

    static Header deserialize(const std::string& header)
    {
        std::vector<std::string> segments = parserHelpers::split(header, " ");

        std::string key = segments[0].substr(0, segments[0].size() - 1);

        segments.erase(segments.begin());

        std::string value = segments[1].substr(0, segments[1].size() - 1);
        Header header1(key, value);
        return header1;
    }
};

#endif
