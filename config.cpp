#include "config.h"
#include <fstream>
#include <iostream>

using namespace std;

// note: utf-8+ chars aren't supported, only ascii works

std::vector<std::wstring> ReadProcessesFromFile(const std::string& filename) {
    std::vector<std::wstring> processNames;
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            processNames.push_back(std::wstring(line.begin(), line.end()));
        }
        file.close();
    }
    else {
        std::cerr << "Could not open file: " << filename << std::endl;
    }
    return processNames;
}

void CreateDefaultProcessesFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "example_process.exe\n";
        file.close();
    }
    else {
        std::cerr << "Could not create file: " << filename << std::endl;
    }
}

std::vector<std::wstring> ReadSettingsFromFile(const std::string& filename) {
    std::vector<std::wstring> settingsLines;
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            settingsLines.push_back(std::wstring(line.begin(), line.end()));
        }
        file.close();
    }
    else {
        std::cerr << "Could not open file: " << filename << std::endl;
    }
    return settingsLines;
}

void CreateDefaultSettingsFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "75\n";   // default refresh rate
        file << "60\n";   // dynamic refresh rate
        file << "5000\n"; // sleep duration (ms)
        file.close();
    }
    else {
        std::cerr << "Could not create file: " << filename << std::endl;
    }
}