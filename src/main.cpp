#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <curl/curl.h>

#include "models/StudentManager.hpp"
#include "services/StudentService.hpp"


int main(int argc, char *argv[]) {

    StudentService studentService;

    std::string studentData;
    studentData = studentService.fetchStudentData();
    StudentManager studentManager(studentData);
    
    return 0;
    
}


