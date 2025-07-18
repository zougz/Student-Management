#include "services/StudentService.hpp"
#include <iostream>
#include <curl/curl.h>

static constexpr int NUM_RETRIES = 3;

// Function defintions
bool handleCurleError(CURLcode error);
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
        for(auto i = 0; i < NUM_RETRIES; i++) {

            curl_easy_setopt(curlHandle, CURLOPT_URL, "https://mocki.io/v1/f6d40d07-be10-4107-9730-5ca9ca7f94f2");
            curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &studentDataBuffer);

            // Perform request
            res = curl_easy_perform(curlHandle);

            if(res != CURLE_OK)
            {
                if(!handleCurleError(res)) { return ""; }
            }  else { break; }
        }
    }
    else 
    {
        throw std::runtime_error("Error initializing curl. Handle not initalized");
    }
    return studentDataBuffer;
}

bool handleCurleError(CURLcode error) {
    std::cout << "Error: ";
    switch(error) {
            std::cout << "Curl failed to initalized" << '\n';
        case CURLE_COULDNT_CONNECT:
            std::cout << "Curl could not connect" << '\n';
        case CURLE_COULDNT_RESOLVE_HOST:
            std::cout << "Curl could not resolve host" << '\n';
        case CURLE_COULDNT_RESOLVE_PROXY:
            std::cout << "Curl could not resolve proxy" << '\n';
        case CURLE_HTTP_RETURNED_ERROR:
            std::cout << "HTTP returned error" << '\n';
        case CURLE_READ_ERROR:
            std::cout << "Curl failed to read" << '\n';
            std::cout << "Too many redirects" << '\n';
        case CURLE_GOT_NOTHING:
            std::cout << "Received nothing!" << '\n';
        case CURLE_RECV_ERROR:
            std::cout << "Failed to receive" << '\n';
            std::cout << "Attempting to retry request" << '\n';
            return true;
        case CURLE_UNSUPPORTED_PROTOCOL:
        case CURLE_FAILED_INIT: // Failed curl_easy_init
        case CURLE_TOO_MANY_REDIRECTS:  
        default:
            return false; // Error - Do NOT retry
    }
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
