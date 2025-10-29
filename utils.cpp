#include "utils.h"
#include <windows.h>

void HideConsole() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
}