#include <future>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <curl/curl.h>
#include <string>

#include "models/StudentManager.hpp"
#include "services/StudentService.hpp"


static constexpr int maxInput = 20;
static bool running = true;

void printMainHelpPrompt() {
    std::cout << "Enter 1: To View All Data \n Enter 2: To search for specific student \
        \n Enter 3: To exit Program" << '\n';
    std::cout << "Press 'h' for help" << '\n';
}

int displayAllMenu() {
    
    int numRetries = 3;
    int attempt = 0;
    std::string userInput;
    bool success = false;

    while(attempt < numRetries && success == false) {
        std::cout << "View All Data selected\n Select View:\n 1: Alphabetical(last name)\
            2: GPA(Largest to Lowest)\n 3:GPA(Lowest to Highest)\n";

        std::cin >> userInput;

        int inputSize = 1; // In this case only expect user input to be single character
        if(userInput.size() > inputSize) { 
            std::cout << "User input is too large!!, Try Again" << '\n';
        } else {
            switch(userInput) {
                case 1:
                    success = true;
                    // Handle Alphabetical
                    break;
                case 2:
                    success = true;
                    // Handle gpa descending
                    break;
                case 3:
                    success = true;
                    // Handle gpa ascending
                    break;
                default:
                    std::cout << "Invalid user input" << '\n';
                    success = false;
                    break;
            }
        }
    }
}

int populateStudentManager(StudentService& studentService, StudentManager& studentManager) {
 
    std::string studentBuffer = studentService.fetchStudentData(); 
    int result = studentManager.parseRawStudentData(studentBuffer);
}

int main(int argc, char *argv[]) {

    StudentService studentService;
    std::string studentData;
    bool parseSuccess = false;
    StudentManager studentManager;
    
    std::future<int> dataFuture = std::async(std::launch::async , [&]() {
       return populateStudentManager(studentService, studentManager);
    }
    std::cout << "Welcome to the Student Database!" << '\n';
    printMainHelpPrompt();

    std::string userInput;
    bool dataLoaded = false;

    while(running) {

        std::cin >> userInput; 
        if(userInput.size() > maxInput) {
            std::cout << "ERROR: User input to too large! Try Again" << '\n';
        } else {
            if(!dataLoaded && dataFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                int studentPullResult = dataFuture.get();
                if(studentPullResult == -1) {
                    std::cout << "Failed to fetch data from database" << '\n';
                    break;
                }
                dataLoaded = true;
            }
            switch (userInput) {
                case 1:
                    displayAllMenu();
                    break;
                case 2:
                    break;
                case 3:
                    running = false;
                    //TODO:May want to write to some save storage
                    //saveState();
                    break;
                default:
                    // Handle some error
                    break;
                    
            }
        }
    } 
    return 0;
}


