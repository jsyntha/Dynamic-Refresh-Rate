#include "display_manager.h"
#include <windows.h>

using namespace std;

void ChangeRefreshRate(int hz) {
    DEVMODE dm;
    ZeroMemory(&dm, sizeof(dm));
    dm.dmSize = sizeof(dm);

    if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm)) {
        dm.dmDisplayFrequency = hz;
        ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
    }
}