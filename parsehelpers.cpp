#include"parserhelpers.h"
#include<string>
#include<iostream>

using namespace std;

std::vector<std::string>
parserHelpers::split(const std::string& str, const std::string& del) noexcept
{
    std::vector<std::string> tokens = std::vector<std::string>();
    std::string strCopy = str;

    std::size_t pos;
    std::string token;
    while ((pos = strCopy.find(del)) != std::string::npos)
    {
        token = strCopy.substr(0, pos);
        strCopy.erase(0, pos + del.length());

        tokens.push_back(token);
    }

    if (strCopy.length() > 0)
    {
        tokens.push_back(strCopy);
    }
    return tokens;
}


bool
parserHelpers::validateStatusLine(const std::string& line) {
    std::vector<std::string> tokens = parserHelpers::split(line, "/");
    std::string result = tokens[0];
    // word before '/' delimiter should be http

    if (result != "HTTP") {
        std::cout<< result << "!=HTTP";
        return false;
    }
    tokens = parserHelpers::split(line, " ");
    result = tokens[0];
    // Version will be in digits. It should contain only 2 digits separated by '.'
    if (result.substr(6, 1) != ".") {
        cout<<"Invalid version"<<endl;
        return false;
    }
    std::string major_version = result.substr(5, 1);
    std::string minor_version = result.substr(7, 1);
    if (!isdigit(major_version[0]) ||
        !isdigit(minor_version[0])) {
        cout<<"Invalid version number"<< stoi(result.substr(5, 1)) << "minor version" << stoi(result.substr(7, 1))<<  endl;
        return false;
    }
    result = tokens[1];
    std::string statusCode = result.substr(0, 3);
    uint32_t statusCode_int = stoi(statusCode);
    if ((statusCode_int < 100 || statusCode_int > 999)) {
        cout<<"Invalid status code" << statusCode_int <<endl;
        return false;
    }
    return true;
}

bool
parserHelpers::validateHeaderLine(const std::string &line) {
    size_t found = line.find(':');
    if (found == string::npos) return false;
    std::vector<std::string> tokens = parserHelpers::split(line, ":");
    std::string result = tokens[0];
    int begin = 0;
    int end = result.length();
  for (char const &c: result) {
        if (!isalnum(c) && (c != '-')) {
            return false;
        }
  }

    std::string value  = tokens[1];
    // If there is no word after the headername, mark it as invalid header
    if (!value.length()) {
        return false;
    }
    for (char const &c: value) {
        if (!isprint(c)) {
            return false;
        }
    }
    return true;
}
