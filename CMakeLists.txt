cmake_minimum_required(VERSION 3.10)
project(cpprest_GetCSVServer)

set(CMAKE_CXX_STANDARD 11)
#find_package(openssl REQUIRED)
find_package(cpprestsdk REQUIRED)


add_executable(cpprest_GetCSVServer src/main.cpp src/handler.h src/handler.cpp)

target_link_libraries(cpprest_GetCSVServer PRIVATE cpprestsdk::cpprest)