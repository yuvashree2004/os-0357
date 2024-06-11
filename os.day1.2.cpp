#include <windows.h>
#include <stdio.h>

void copyFile(const char *source, const char *destination) {
    HANDLE hSource, hDestination;
    DWORD bytesRead, bytesWritten;
    char buffer[4096];
    BOOL result;

    // Open the source file for reading
    hSource = CreateFile(
        source,             // Source file name
        GENERIC_READ,       // Open for reading
        0,                  // Do not share
        NULL,               // Default security
        OPEN_EXISTING,      // Open existing file
        FILE_ATTRIBUTE_NORMAL, // Normal file
        NULL);              // No template

    if (hSource == INVALID_HANDLE_VALUE) {
        printf("Could not open source file (error %d)\n", GetLastError());
        return;
    }

    // Create the destination file for writing
    hDestination = CreateFile(
        destination,        // Destination file name
        GENERIC_WRITE,      // Open for writing
        0,                  // Do not share
        NULL,               // Default security
        CREATE_ALWAYS,      // Create new file, always
        FILE_ATTRIBUTE_NORMAL, // Normal file
        NULL);              // No template

    if (hDestination == INVALID_HANDLE_VALUE) {
        printf("Could not create destination file (error %d)\n", GetLastError());
        CloseHandle(hSource);
        return;
    }

    // Copy the file content
    while (TRUE) {
        result = ReadFile(hSource, buffer, sizeof(buffer), &bytesRead, NULL);
        if (!result || bytesRead == 0) {
            // Either an error occurred, or we are done reading
            break;
        }

        result = WriteFile(hDestination, buffer, bytesRead, &bytesWritten, NULL);
        if (!result || bytesWritten != bytesRead) {
            // An error occurred while writing
            printf("Error writing to destination file (error %d)\n", GetLastError());
            break;
        }
    }

    // Close both files
    CloseHandle(hSource);
    CloseHandle(hDestination);

    if (result) {
        printf("File copied successfully.\n");
    } else {
        printf("File copy failed.\n");
    }
}

int main() {
    const char *sourceFile = "source.txt";
    const char *destinationFile = "destination.txt";

    copyFile(sourceFile, destinationFile);

    return 0;
}


