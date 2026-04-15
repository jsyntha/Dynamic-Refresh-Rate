#include "config.h"
#include "monitor_service.h"
#include "process_monitor.h"
#include "display_manager.h"

#include <windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// defaults used if settings file is missing or has bad values
const int DEFAULT_REFRESH_RATE = 75;
const int DYNAMIC_REFRESH_RATE = 60;
const int SLEEP_DURATION_MS = 5000;

void RunMonitorService() {
    string settingsFile = "settings/settings.txt";
    string processesFile = "processes.txt";

    ifstream settingsCheck(settingsFile);
    if (!settingsCheck.good()) {
        CreateDefaultSettingsFile(settingsFile);
    }
    settingsCheck.close();

    ifstream processesCheck(processesFile);
    if (!processesCheck.good()) {
        CreateDefaultProcessesFile(processesFile);
    }
    processesCheck.close();

    vector<wstring> settingsLines = ReadSettingsFromFile(settingsFile);

    int defaultRefreshRate = (settingsLines.size() > 0) ? stoi(wstring(settingsLines[0])) : DEFAULT_REFRESH_RATE;
    int dynamicRefreshRate = (settingsLines.size() > 1) ? stoi(wstring(settingsLines[1])) : DYNAMIC_REFRESH_RATE;
    int sleepDurationMs = (settingsLines.size() > 2) ? stoi(wstring(settingsLines[2])) : SLEEP_DURATION_MS;

    vector<wstring> gameProcesses = ReadProcessesFromFile(processesFile);
    bool isGameRunning = false;
    wstring activeProcess = L"";

    while (true) {
        wstring runningProcess = IsAnyProcessRunning(gameProcesses);

        if (!runningProcess.empty()) {
            if (!isGameRunning) {
                wcout << "Process detected: " << runningProcess << ", changing refresh rate to " << dynamicRefreshRate << "Hz\n";
                ChangeRefreshRate(dynamicRefreshRate);
                isGameRunning = true;
                activeProcess = runningProcess;
            }
        }
        else {
            if (isGameRunning) {
                wcout << "Process closed: " << activeProcess << ", reverting refresh rate to " << defaultRefreshRate << "Hz\n";
                ChangeRefreshRate(defaultRefreshRate);
                isGameRunning = false;
                activeProcess = L"";
            }
        }

        Sleep(sleepDurationMs);
    }
}