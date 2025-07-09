#include <fstream>
#include <json/json.h>

class StudentService {

public:

    StudentService();
    ~StudentService();

    Json::Value fetchStudentData();
    Json::Value fetchStoredStudentData();

private:
    
    CURL *curlHandle;
    std::string studentDataBuffer;
};

