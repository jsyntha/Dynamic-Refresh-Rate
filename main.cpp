// Configuration constants
// inside "processes.txt" add the name of the executables, make sure it's line by line.
const int DEFAULT_REFRESH_RATE = 75;  // Default refresh rate
const int DYNAMIC_REFRESH_RATE = 60;  // Dynamic refresh rate when a process is detected (What the refresh rate will be changed to) (Eg. 144hz -> 60hz)
const int SLEEP_DURATION_MS = 5000;   // Sleep duration in milliseconds

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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

std::wstring IsAnyProcessRunning(const std::vector<std::wstring>& processNames) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry)) {
        do {
            for (const auto& processName : processNames) {
                if (!_wcsicmp(entry.szExeFile, processName.c_str())) {
                    CloseHandle(snapshot);
                    return processName;
                }
            }
        } while (Process32Next(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return L"";
}

void ChangeRefreshRate(int hz) {
    DEVMODE dm;
    ZeroMemory(&dm, sizeof(dm));
    dm.dmSize = sizeof(dm);

    if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm)) {
        dm.dmDisplayFrequency = hz;
        ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
    }
}

int main() {
    std::string filename = "processes.txt";
    std::ifstream fileCheck(filename);
    if (!fileCheck.good()) {
        CreateDefaultProcessesFile(filename);
    }
    fileCheck.close();

    std::vector<std::wstring> gameProcesses = ReadProcessesFromFile(filename);
    bool isGameRunning = false;
    std::wstring activeProcess = L"";

    while (true) {
        std::wstring runningProcess = IsAnyProcessRunning(gameProcesses);

        if (!runningProcess.empty()) {
            if (!isGameRunning) {
                std::wcout << "Process detected: " << runningProcess << ", changing refresh rate to " << DYNAMIC_REFRESH_RATE << "Hz\n";
                ChangeRefreshRate(DYNAMIC_REFRESH_RATE);
                isGameRunning = true;
                activeProcess = runningProcess;
            }
        }
        else {
            if (isGameRunning) {
                std::wcout << "Process closed: " << activeProcess << ", reverting refresh rate to " << DEFAULT_REFRESH_RATE << "Hz\n";
                ChangeRefreshRate(DEFAULT_REFRESH_RATE);
                isGameRunning = false;
                activeProcess = L"";
            }
        }

        Sleep(SLEEP_DURATION_MS);
    }

    return 0;
}
