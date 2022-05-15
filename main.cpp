#include <iostream>

#include "responseparser.h"

using namespace std;

int main(int, char**) {
    std::string str =
            "HTTP/1.1 302 Found\r\n"
            "cache-control: public\r\n"
            "Transfer-encoding: chunked \r\n"
            "Invalid-header \r\n"
            "date: Tue, 22 Jun 2021 22:24:42 GMT\r\n";

    //Output
    //HTTP Version:1.0
    //Status:302
    //Number of valid headers:3
    //Number of invalid headers:1

    responseParser response = responseParser::parseHttpResponse(str);
    cout<<response<<endl;
    //
    return 0;
}