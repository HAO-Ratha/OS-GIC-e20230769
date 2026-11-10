
#include <stdio.h>
#include <windows.h>

int main(void) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // Initialize structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Display parent process ID
    printf("Parent process (PID: %lu) - creating child...\n",
           GetCurrentProcessId());

    // Create child process
    if (!CreateProcess(
            "C:\\Windows\\System32\\mspaint.exe",
            NULL,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi
        ))
    {
        fprintf(stderr, "CreateProcess failed (error %lu).\n",
                GetLastError());
        return 1;
    }

    // Display child process information
    printf("\nChild process created successfully!\n");
    printf("Child Process ID: %lu\n", pi.dwProcessId);
    printf("Child Thread ID:  %lu\n", pi.dwThreadId);

    // Wait for child process to terminate
    printf("\nParent: Waiting for Microsoft Paint to close...\n");
    printf("Open Task Manager to observe the child process.\n");
    printf("Close Microsoft Paint to continue.\n");

    WaitForSingleObject(pi.hProcess, INFINITE);

    printf("\nParent: Child process has exited.\n");

    // Release resources
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    printf("Parent: Resources cleaned up.\n");

    return 0;
}
