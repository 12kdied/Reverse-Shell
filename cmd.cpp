#include <Windows.h>
#include <thread>
void hideConsoleWindow() {
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
}