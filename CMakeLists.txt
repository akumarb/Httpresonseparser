cmake_minimum_required(VERSION 3.21)
project(HTTPRESPONSEPARSER)
set(CMAKE_CXX_STANDARD 17)

add_executable(HTTPRESPONSEPARSER main.cpp responseparser.h header.h parserhelpers.h parsehelpers.cpp)


