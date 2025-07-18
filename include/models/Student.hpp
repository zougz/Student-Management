#pragma once

#include <string>
#include <utility>
#include <vector>

class Student {
public:
    Student() : 
        id(-1),
        username(""),
        name("", ""),
        location(""),
        major(""),
        gender(""),
        courses({}),
        age(-1),
        gpa(-1.0f) {}

    void setId(int newId) { id = newId; }
    void setUsername(const std::string& newUsername) { username = newUsername; }
    void setName(const std::string& newFirstName, const std::string& newLastName) {
        std::pair name = std::make_pair(newFirstName, newLastName);
    }
    void setLocation(const std::string& newLocation) { location = newLocation; }
    void setMajor(const std::string& newMajor) { major = newMajor; }
    void setGender(const std::string& newGender) { gender = newGender; }
    void setAge(int newAge) { age = newAge; }
    void setGpa(float newGpa) { gpa = newGpa; }
    void appendCourse(std::string course) {
        courses.push_back(course);
    }

    int getId() { return id; }
    std::string getUsername() { return username; }
    std::pair<std::string, std::string> getName() { return name; }
    std::string getLocation() { return location; }
    std::string getMajor() { return major; }
    std::string getGender() { return gender; }
    std::vector<std::string> getCourses() { return courses; }

private:
    int id;
    std::string username;
    std::pair <std::string, std::string> name;
    std::string location;
    std::string major;
    std::string gender;
    std::vector<std::string> courses;
    int age;
    float gpa;
};
