# KeepMeAwake

**KeepMeAwake** is a simple C++ program created to prevent your PC from going to sleep, without having to change your screen off / sleep timeouts in Windows. By default, it will run until the Enter key is pressed.  It has been designed to work on Windows XP or newer, but currently has only been tested on Windows 10 & 11.

Command Usage:   KeepMeAwake.exe [-option] [value]

Parameters:
- 
- `-h` Runs the help function to show parameters that can be used with this program
- `-s` Allows the screen to sleep (if configured in Windows) while keeping the computer awake
- `-t <seconds>` Keeps the program running for the specified number of seconds
