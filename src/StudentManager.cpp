#include "models/StudentManager.hpp"

#include "models/Student.hpp"

#include "json/json.h"
#include <iostream>

StudentManager::StudentManager(const std::string& studentData) : rawStudentData(studentData) {
    parseRawStudentData(rawStudentData);
}

StudentManager::~StudentManager() {}

void StudentManager::parseRawStudentData(const std::string& data) {
    
    Json::Value studentProfiles;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(data, studentProfiles);
    if(!parsingSuccessful) {
        //TODO:: Will need to add some form of retry on fetch
        std::cout << "Error parsing the string. Re-Fetech" << std::endl;
    }


    for(const auto& student : studentProfiles) {

        std::cout << student << std::endl;
        std::string id = student["id"].asString();
        std::string userName = student["username"].asString();
        int age = student["profile"]["age"].asInt();
        std::string firstName = student["profile"]["firstName"].asString();
        std::string lastName = student["profile"]["lastName"].asString();
        std::string location = student["profile"]["location"].asString();
        std::string major = student["profile"]["major"].asString();
        std::string gender = student["profile"]["gender"].asString();
        float gpa = student["profile"]["gpa"].asFloat();
        
        for(const auto& course : student["profile"]["courses"]) {
            std::cout << course.asString() << std::endl;
        }

        // TODO:: Add students 
        //Student student(id, username, firstName, lastName, location, }
     }
}
