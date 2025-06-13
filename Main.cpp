#include <iostream>
#include <Windows.h>
#include <conio.h>

int main() {
    // This prevents the OS from going to sleep
    SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED);

    std::cout << "Your system will now stay awake.  Press the Enter key to exit this program...";

    // This keeps the program running until the user presses the Enter key
    char inputkey = 0;
    do {
        inputkey = _getch();
    } while (inputkey != '\r' && inputkey != '\n');

    // This returns the OS to its previous state to allow it to go to sleep
    SetThreadExecutionState(ES_CONTINUOUS);
    return 0;
}