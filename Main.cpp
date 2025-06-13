#include <iostream>
#include <Windows.h>

int main() {
	// This prevents the OS from going to sleep
	SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED);

	std::cout << "Your system will now stay awake.  Press the Enter key to exit this program...";
	std::cin.get();

	//This returns the OS to it's previous state to allow it to go to sleep
	SetThreadExecutionState(ES_CONTINUOUS);
	return 0;
}