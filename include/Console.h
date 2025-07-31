#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>
#include <vector> // For potential future use, e.g., storing lines

// Platform-specific includes
#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#elif defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || \
      defined(__OpenBSD__) || defined(__linux__) || defined(__sun) || defined(__sun__)
    #include <sys/ioctl.h>
    #include <unistd.h>
    #include <termios.h> // Though not directly used in the Console class for now, good to keep for terminal control
#endif

// Structure to hold window dimensions
struct WindowSize {
    int width;
    int height;
    WindowSize(int w = 0, int h = 0) : width(w), height(h) {}
};

// Console class for managing console output and properties
class Console {
public:
    Console(); // Constructor to initialize window size
    ~Console() = default; // Default destructor

    void clearScreen() const;
    WindowSize getWindowSize() const;
    void printLineOfChars(char character, int length) const;
    void printBorder(char borderChar = 'X') const;
    void printCentered(const std::string& text, char borderChar = 'X') const;
    std::string getSystemInfo() const;

private:
    WindowSize currentSize; // Store the current console size
    void updateWindowSize(); // Helper to update currentSize
};

#endif // CONSOLE_H
