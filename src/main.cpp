#include <future>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <curl/curl.h>
#include <string>

#include "models/StudentManager.hpp"
#include "services/StudentService.hpp"


static constexpr int maxInputMenu = 1;
static constexpr int numRetries = 3;
static constexpr int maxNameLength = 15;
static bool running = true;

void printMainHelpPrompt() {
    std::cout << "Enter 1: To View All Data \nEnter 2: To search for specific student \
        \nEnter 3: To exit Program" << '\n';
    std::cout << "Press 'h' for help" << '\n';
}

int displayAllMenu() {
    
    int attempt = 0;
    std::string userInput;
    bool success = false;

    while(attempt < numRetries && success == false) {
        std::cout << "View All Data selected\n Select View:\n 1: Alphabetical(last name)\
            2: GPA(Largest to Lowest)\n 3:GPA(Lowest to Highest)\n";

        std::cin >> userInput;

        if(userInput.size() > maxInputMenu) { 
            std::cout << "User input is too large!!, Try Again" << '\n';
        } else {
            char command = userInput[0];
            switch(command) {
                case '1':
                    success = true;
                    // Handle Alphabetical
                    break;
                case '2':
                    success = true;
                    // Handle gpa descending
                    break;
                case '3':
                    success = true;
                    // Handle gpa ascending
                    break;
                case 'h':
                    break;
                default:
                    std::cout << "Error: Invalid user input. Try again" << '\n';
                    ++attempt;
                    break;
            }
        }
    }

    return success;
}

bool isNameValid(const std::string& name) {
    return std::all_of(name.begin(), name.end(), [](char ch) {
            return std::isalpha(static_cast<unsigned char>(ch)) || ch == '-';
    });
}

int userInputName(std::string& firstName, std::string& lastName) {
    for(auto tries = 0; tries < numRetries; ++tries) {
        std::cout << "Enter student last name\n";
        std::cin >> lastName;
        if(lastName.size() > maxNameLength && !isNameValid(lastName)) {
            std::cout << "Error: Inputed last name is too long! Retry\n";
        } else {
            std::cout << "Enter student first name\n";
            std::cin >> firstName;
            if(lastName.size() > maxNameLength && isNameValid(lastName)) {
                std::cout << "Error: Inputed last name is too long! Retry\n";
            } else { return 0; } 
        }
    }
    return -1;
}

int singleStudentRequest(const StudentManager& studentManager) {
    std::string firstName;
    std::string lastName;
    if(userInputName(firstName, lastName) == -1) return -1;
    studentManager.requestSingleStudentData(firstName, lastName);
}

int populateStudentManager(StudentService& studentService, StudentManager& studentManager) {

    int result; 
    for(auto tries = 0; tries < numRetries; ++tries) {
        std::string studentBuffer = studentService.fetchStudentData(); 
        result = studentManager.parseRawStudentData(studentBuffer);
        if (result == 0) break;
    }
    return result;
}

int main(int argc, char *argv[]) {

    StudentService studentService;
    std::string studentData;
    bool parseSuccess = false;
    StudentManager studentManager;
    
    std::future<int> dataFuture = std::async(std::launch::async , [&]() {
       return populateStudentManager(studentService, studentManager);
    });

    std::cout << "Welcome to the Student Database!" << '\n';
    printMainHelpPrompt();

    std::string userInput;
    bool dataLoaded = false;

    while(running) {

        std::cin >> userInput; 
        if(userInput.size() > maxInputMenu) {
            std::cout << "ERROR: User input invalid! Try Again" << '\n';
        } else {
            if(!dataLoaded && dataFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                int studentPullResult = dataFuture.get();
                if(studentPullResult == -1) {
                    std::cout << "Error: Failed to fetch data from database" << '\n';
                    running = false;
                    break;
                }
                dataLoaded = true;
            }
            char command = userInput[0];
            switch (command) {
                case '1':
                    displayAllMenu();
                    break;
                case '2':
                    singleStudentRequest(studentManager);
                    break;
                case '3':
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


