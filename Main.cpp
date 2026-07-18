#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <chrono>
#include <thread>

HANDLE hMutex = NULL;

void timer(long long int seconds) {
	if (seconds <= 0) {
		std::cout << "Invalid number of seconds: " << seconds << std::endl;
		return;
	}

	std::cout << "staying awake for " << seconds << " seconds";
	auto start = std::chrono::steady_clock::now();
	while (true) {
		auto now = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
		if (elapsed >= seconds) {
			break;
		}

		std::cout << ".";
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	std::cout << std::endl;
}

void cleanup() {
	SetThreadExecutionState(ES_CONTINUOUS);
	if (hMutex) {
		CloseHandle(hMutex);
		hMutex = NULL;
	}
	std::cout << "Exiting program!" << std::endl;
}

BOOL WINAPI ConsoleHandler(DWORD signal) {
	if (signal == CTRL_C_EVENT || signal == CTRL_CLOSE_EVENT || signal == CTRL_BREAK_EVENT || signal == CTRL_LOGOFF_EVENT || signal == CTRL_SHUTDOWN_EVENT) {
		cleanup();
		return 1;
	}
	return 1;
}

void pause() {
	char inputkey = 0;
	do {
		inputkey = _getch();
	} while (inputkey != '\r' && inputkey != '\n');
}

int main(int argc, char* argv[]) {
	hMutex = CreateMutexA(NULL, FALSE, "KeepMeAwake_SingleInstance_Mutex");

	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		std::cout << "Another instance of KeepMeAwake is already running. Please close any other instances and try again.\nPress Enter key to exit..." << std::endl;
		if (hMutex) {
			CloseHandle(hMutex);
		}
		pause();
		return 1;
	}
	
	if (!SetConsoleCtrlHandler(ConsoleHandler, TRUE)) {
		std::cout << "Error: Could not set console control handler." << std::endl;
		return 1;
	}

	std::atexit(cleanup);
	std::cout << "KeepMeAwake Version 1.1.0, Created by Dylan Aviles\n" << std::endl;
	bool displayCanSleep = false, timed = false; long long seconds = NULL;
	
	if (argc != 1) {
		for (int i = 1; i < argc; ++i) {
			if (argv[i][0] == '-') {
				char option = argv[i][1];
				switch (option) {
				case 'h':
				case 'H':
					std::cout << "Command Usage:   KeepMeAwake.exe [-option] [value]\n" << std::endl;

					std::cout << " No Options Used:  Keeps the program running until the Enter key is pressed." << std::endl;
					std::cout << "              -s:  Allows the screen to sleep (if configured in Windows) while keeping the computer awake" << std::endl;
					std::cout << "    -t <seconds>:  Keeps the program running for the specified number of seconds\n" << std::endl;

					return 0;

				case 's':
				case 'S':
					std::cout << "Option -s selected, now allowing the screen to sleep" << std::endl;
					displayCanSleep = true;
					break;

				case 't':
				case 'T':
					if (i + 1 < argc) {
						seconds = std::atoll(argv[i + 1]);
						timed = true;
					}
					else {
						std::cout << "No argument provided for option -t: seconds\n Usage: KeepMeAwake.exe -t 60\n" << std::endl;
						return 1;
					}
					i++;
					break;
				default:
					std::cout << "Unknown option: " << option << ", ";
					return 1;
				}
			}
			else {
				std::cout << "Invalid argument: " << argv[i] << ", ";
				return 1;
			}
		}
	}

	if (displayCanSleep) {
		SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED);
	}
	else {
		SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED | ES_AWAYMODE_REQUIRED);
	}

	if (timed) {
		std::cout << "Option -t selected, ";
		timer(seconds);
	}
	else {
		std::cout << "Your system will now stay awake until you press the Enter key..." << std::endl;
		pause();
	}

	return 0;
}


// Copyright (c) 2025-2026 Dylan Aviles
// Licensed under MIT (https://github.com/davil544/KeepMeAwake/blob/master/LICENSE.md)