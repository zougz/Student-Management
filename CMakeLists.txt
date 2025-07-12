cmake_minimum_required(VERSION 3.17)
project(StudentManagement CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET "11.3" CACHE STRING "Minimum macOS version")

find_package(CURL REQUIRED)
find_package(jsoncpp REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(studentManagement 
    src/StudentManager.cpp
    src/StudentService.cpp
    src/main.cpp)

target_link_libraries(studentManagement 
    CURL::libcurl
    JsonCpp::JsonCpp
)
