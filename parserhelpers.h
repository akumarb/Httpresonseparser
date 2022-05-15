//
// Created by akb on 2022-05-14.
//

#ifndef HTTPRESPONSEPARSER_PARSERHELPERS_H
#define HTTPRESPONSEPARSER_PARSERHELPERS_H

#include<vector>
#include<string>

namespace parserHelpers {
    // Helper Method to split HTML response
    std::vector<std::string> split(const std::string& str, const std::string& del) noexcept;
    // Helper Method to validate Header status
    bool validateStatusLine(const std::string& line);
    // Helper Method to validate Headers
    bool validateHeaderLine(const std::string& line);
}

#endif //HTTPRESPONSEPARSER_PARSERHELPERS_H