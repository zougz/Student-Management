#include "services/StudentService.hpp"
#include <iostream>
#include <curl/curl.h>

static constexpr int NUM_TRIES = 3;


// Function defintions
int handleCurleError(CURLcode error);
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    
StudentService::StudentService() {
    std::cout << "Initializing curl" << std::endl;
    curlHandle = curl_easy_init();
}

StudentService::~StudentService() {
    curl_easy_cleanup(curlHandle);
}

std::string StudentService::fetchStudentData() {
    if(curlHandle) {

        // tells libcurl how to behave, sets appropriate options
        
        CURLcode res;
        for(auto i = 0; i < NUM_TRIES; i++) {

            curl_easy_setopt(curlHandle, CURLOPT_URL, "https://mocki.io/v1/f6d40d07-be10-4107-9730-5ca9ca7f94f2");
            curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &studentDataBuffer);

            // Perform request
            res = curl_easy_perform(curlHandle);

            // TODO:: Handle res error codes
            if(res != CURLE_OK)
            {
                std::cout << "Handling error" << std::endl;
                handleCurleError(res);
            }
            else
            {
                break;
            }
        }

        curl_easy_cleanup(curlHandle);
    }
    else 
    {
        throw std::runtime_error("Error initializing curl. Handle not initalized");
    }
    return studentDataBuffer;
}

int handleCurleError(CURLcode error) {
    switch(error) {
        case CURLE_UNSUPPORTED_PROTOCOL:
        case CURLE_FAILED_INIT:
        case CURLE_COULDNT_CONNECT:
        case CURLE_COULDNT_RESOLVE_HOST:
        case CURLE_COULDNT_RESOLVE_PROXY:
        case CURLE_HTTP_RETURNED_ERROR:
        case CURLE_READ_ERROR:
        case CURLE_TOO_MANY_REDIRECTS:
        case CURLE_GOT_NOTHING:
        case CURLE_RECV_ERROR:
        default:
            return -1; // Error - Do NOT retry
    }
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
