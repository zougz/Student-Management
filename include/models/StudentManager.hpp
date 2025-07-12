#include "Student.hpp"
#include <map>

class StudentManager {
public:
    StudentManager(const std::string& studentData); 
    ~StudentManager();

    void parseRawStudentData(const std::string& data);
     
    Student getStudent(std::string name);
    Student getStudent(int id);

private:
    std::map<int, Student> studentMap;
    std::string rawStudentData;
};
