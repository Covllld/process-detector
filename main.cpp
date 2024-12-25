#include <iostream>
#include <windows.h>
#include <psapi.h>

void listProcesses() {
    DWORD processIds[1024], cbNeeded, processCount;

    if (EnumProcesses(processIds, sizeof(processIds), &cbNeeded)) {
        processCount = cbNeeded / sizeof(DWORD);
        for (unsigned int i = 0; i < processCount; i++) {
            DWORD pid = processIds[i];
            if (pid != 0) {
                char processName[MAX_PATH] = "<unknown>";
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
                if (hProcess) {
                    HMODULE hMod;
                    if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
                        GetModuleBaseNameA(hProcess, hMod, processName, sizeof(processName));
                    }
                    CloseHandle(hProcess);
                }
                std::cout << "PID: " << pid << " Process: " << processName << std::endl;
            }
        }
    }
}



int main() {
    listProcesses();
    std::cin.get();
    return 0;
}


