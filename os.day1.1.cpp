#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // Initialize the memory for STARTUPINFO and PROCESS_INFORMATION
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create a new process
    if (!CreateProcess(NULL,   // No module name (use command line)
                       "C:\\Windows\\System32\\notepad.exe", // Command line
                       NULL,           // Process handle not inheritable
                       NULL,           // Thread handle not inheritable
                       FALSE,          // Set handle inheritance to FALSE___
                       0,              // No creation flags
                       NULL,           // Use parent's environment block
                       NULL,           // Use parent's starting directory 
                       &si,            // Pointer to STARTUPINFO structure
                       &pi)           // Pointer to PROCESS_INFORMATION structure
    ) {
        fprintf(stderr, "CreateProcess failed (%d).\n", GetLastError());
        return 1;
    }

    // Output parent process ID
    printf("Parent Process ID: %lu\n", GetCurrentProcessId());

    // Output child process ID
    printf("Child Process ID: %lu\n", pi.dwProcessId);

    // Wait until child process exits
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}


