#include <fstream>
#include <json/json.h>
#include <curl/curl.h>

class StudentService {
public:

    StudentService();
    ~StudentService();

    std::string fetchStudentData();
    Json::Value fetchStoredStudentData();

private:
    CURL *curlHandle;
    std::string studentDataBuffer;
};

