#include "monitor_service.h"

#include "config.h"
#include "process_monitor.h"
#include "display_manager.h"

#include <windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// config
const int DEFAULT_REFRESH_RATE = 75;
const int DYNAMIC_REFRESH_RATE = 60;
const int SLEEP_DURATION_MS = 5000;

void RunMonitorService() {
    string filename = "processes.txt";
    ifstream fileCheck(filename);

    if (!fileCheck.good()) {
        CreateDefaultProcessesFile(filename);
    }
    fileCheck.close();

    vector<wstring> gameProcesses = ReadProcessesFromFile(filename);
    bool isGameRunning = false;
    wstring activeProcess = L"";

    while (true) {
        wstring runningProcess = IsAnyProcessRunning(gameProcesses);

        if (!runningProcess.empty()) {
            if (!isGameRunning) {
                wcout << "Process detected: " << runningProcess << ", changing refresh rate to " << DYNAMIC_REFRESH_RATE << "Hz\n";
                ChangeRefreshRate(DYNAMIC_REFRESH_RATE);
                isGameRunning = true;
                activeProcess = runningProcess;
            }
        }
        else {
            if (isGameRunning) {
                wcout << "Process closed: " << activeProcess << ", reverting refresh rate to " << DEFAULT_REFRESH_RATE << "Hz\n";
                ChangeRefreshRate(DEFAULT_REFRESH_RATE);
                isGameRunning = false;
                activeProcess = L"";
            }
        }
        Sleep(SLEEP_DURATION_MS);
    }
}