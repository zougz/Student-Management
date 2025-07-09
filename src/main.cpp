#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <curl/curl.h>



int main(int argc, char *argv[]) {

    StudentService studentService;

    std::string studentData;
    studentData = studentService.fetchStudentData();

    
    
    

    return 0;
}


