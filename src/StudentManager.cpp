#include "models/StudentManager.hpp"

#include "models/Student.hpp"

#include "json/json.h"
#include <iostream>

// Class defines
StudentManager::StudentManager() {}

StudentManager::~StudentManager() {}

int StudentManager::parseRawStudentData(const std::string& data) {
    
    Json::Value studentProfiles;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(data, studentProfiles);
    if(!parsingSuccessful) {
        //TODO:: Will need to add some form of retry on fetch
        std::cout << "Error parsing the string. Re-Fetch" << std::endl;
        return -1; 
    }

    for(const auto& student : studentProfiles) {

        Student studentObj;
        studentObj.setId(student["id"].asInt());
        studentObj.setUsername(student["username"].asString());
        studentObj.setAge(student["profile"]["age"].asInt());
        studentObj.setName(student["profile"]["firstName"].asString(), 
                           student["profile"]["lastName"].asString());
        studentObj.setLocation(student["profile"]["location"].asString());
        studentObj.setMajor(student["profile"]["major"].asString());
        studentObj.setGender(student["profile"]["gender"].asString());
        studentObj.setGpa(student["profile"]["gpa"].asFloat());
        
        for(const auto& course : student["profile"]["courses"]) {
            studentObj.appendCourse(course.asString());
        }

        studentMap[studentObj.getId()] = studentObj;
     }

    return 0; // success
}
