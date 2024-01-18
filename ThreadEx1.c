#include <stdio.h>
#include <windows.h>

typedef struct {
    int start;
    int end;
    int step;
    int* locale;
} ThreadData;

int globale = 0;

DWORD WINAPI SumThreadFunction(LPVOID param) {
    ThreadData* data = (ThreadData*)param;

    int sum = 0;
    for (int i = data->start; i <= data->end; i += data->step) {
        sum += i;
        globale = globale +1;
        *(data->locale) += 1 ;
    }

    // Returning the sum as a DWORD (DWORD is the return type for a thread)
    printf("Thread function: Sum calculated = %d\n", sum);
    return (DWORD)sum;
}

int main() {
    int locale = 0;
    ThreadData data = {1, 100, 10, &locale};

    // Create a thread
    HANDLE threadHandle = CreateThread(
        NULL,                 // Default security attributes
        0,                    // Default stack size
        SumThreadFunction,    // Thread function
        &data,                // Data to pass to the thread function
        0,                    // Default creation flags
        NULL                  // Pointer to thread identifier
    );

    if (threadHandle == NULL) {
        fprintf(stderr, "Error creating thread.\n");
        return 1;
    }

    // Main function execution
    printf("Main function: Started\n");

    // Do some work in the main function while the thread is running
    for (int i = 0; i < 5; ++i) {
        printf("Main function: Working... (%d)\n", i);
        Sleep(1000); // Sleep for 1 second
    }

    printf("Main function: Finished working\n");

    // Wait for the thread to finish
    WaitForSingleObject(threadHandle, INFINITE);

    // Get the thread exit code (sum)
    DWORD exitCode;
    GetExitCodeThread(threadHandle, &exitCode);

    // Close the thread handle
    CloseHandle(threadHandle);

    printf("Main function: Thread function result = %d\n", exitCode);

    printf("variable globale : %d\n", globale);
    printf("variable locale : %d\n", local);

    return 0;
}

