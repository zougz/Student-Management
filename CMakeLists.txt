cmake_minimum_required(VERSION 3.17)
project(StudentManagement CXX)

find_package(CURL REQUIRED)

add_executable(studentManagement src/main.cpp)

target_link_libraries(studentManagement CURL::libcurl)
