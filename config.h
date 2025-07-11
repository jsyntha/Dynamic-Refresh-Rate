#pragma once
#include <string>
#include <vector>
#include <windows.h>

std::vector<std::wstring> ReadProcessesFromFile(const std::string& filename);
void CreateDefaultProcessesFile(const std::string& filename);