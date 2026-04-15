#pragma once
#include <string>
#include <vector>
#include <windows.h>

std::vector<std::wstring> ReadProcessesFromFile(const std::string& filename);
void CreateDefaultProcessesFile(const std::string& filename);

std::vector<std::wstring> ReadSettingsFromFile(const std::string& filename);
void CreateDefaultSettingsFile(const std::string& filename);