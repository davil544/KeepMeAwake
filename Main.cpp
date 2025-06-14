#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <chrono>
#include <thread>

void timer(long long int seconds) {
	if (seconds <= 0) {
		std::cout << "Invalid number of seconds: " << seconds << std::endl;
		return;
	}

	// This prints one dot per second to the console until the specified time has elapsed
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

int main(int argc, char* argv[]) {
	std::cout << "KeepMeAwake Version 1.0.1-prerelease, Created by Dylan Aviles\n" << std::endl;

	// This prevents the OS from going to sleep
	SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED);

	// This checks if any arguments have passed to the program
	if (argc == 1) {
		std::cout << "Your system will now stay awake until you press the Enter key..." << std::endl;

		// This keeps the program running until the user presses the Enter key
		char inputkey = 0;
		do {
			inputkey = _getch();
		} while (inputkey != '\r' && inputkey != '\n');
	}
	else {
		for (int i = 1; i < argc; ++i) {
			if (argv[i][0] == '-') {
				char option = argv[i][1];
				switch (option) {
				case 'h':
				case 'H':
					std::cout << "Command Usage:   KeepMeAwake.exe [-option] [value]\n" << std::endl;

					std::cout << " No Options Used:  Keeps the program running until the Enter key is pressed." << std::endl;
					std::cout << "    -t <seconds>:  Keeps the program running for the specified number of seconds" << std::endl;

					break;
				case 't':
				case 'T':
					std::cout << "Option -t selected, ";
					if (i + 1 < argc) {
						timer(std::atoll(argv[i + 1]));
					}
					else {
						std::cout << "No argument provided for option -t: seconds\n Usage: KeepMeAwake.exe -t 60" << std::endl;
					}
					i++;
					break;
				default:
					std::cout << "Unknown option: " << option << ", ";
				}
			}
			else {
				std::cout << "Invalid argument: " << argv[i] << ", ";
			}
		}
	}

	// This returns the OS to its previous state to allow it to go to sleep
	SetThreadExecutionState(ES_CONTINUOUS);
	std::cout << "Exiting program!" << std::endl;
	return 0;
}


// Copyright (c) 2025 Dylan Aviles
// Licensed under MIT (https://github.com/davil544/KeepMeAwake/blob/master/LICENSE.md)