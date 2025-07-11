#include "process_monitor.h"
#include <windows.h>
#include <tlhelp32.h>

using namespace std;

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