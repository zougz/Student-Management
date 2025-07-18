#include "Student.hpp"
#include <unordered_map>

class StudentManager {
public:
    StudentManager(); 
    ~StudentManager();

    int parseRawStudentData(const std::string& data);
     
    Student getStudent(std::string name);
    Student getStudent(int id);

private:
    std::string rawStudentData;
    std::unordered_map<int, Student> studentMap;
};
