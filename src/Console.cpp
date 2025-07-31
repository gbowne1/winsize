#include "../include/Console.h"
#include <stdexcept>

Console::Console() {
    updateWindowSize();
}

void Console::updateWindowSize() {
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Failed to get console handle.");
    }
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        currentSize.width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        currentSize.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    } else {
        // Fallback or error if unable to get console info
        currentSize.width = 80;
        currentSize.height = 24;
        std::cerr << "Warning: Could not get console buffer info. Using default size." << std::endl;
    }
#else
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        currentSize.width = w.ws_col;
        currentSize.height = w.ws_row;
    } else {
        // Fallback or error if unable to get window size
        currentSize.width = 80;
        currentSize.height = 24;
        std::cerr << "Warning: Could not get terminal window size. Using default size." << std::endl;
    }
#endif

    // Ensure minimum reasonable dimensions
    if (currentSize.width <= 0) currentSize.width = 80;
    if (currentSize.height <= 0) currentSize.height = 24;
}

void Console::clearScreen() const {
#if defined(_WIN32)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Failed to get console handle for clearing screen.");
    }
    COORD screenPos = {0, 0};
    DWORD writtenChars;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    if (GetConsoleScreenBufferInfo(hConsole, &consoleInfo)) {
        FillConsoleOutputCharacter(hConsole, ' ', static_cast<DWORD>(consoleInfo.dwSize.X) * consoleInfo.dwSize.Y, screenPos, &writtenChars);
        SetConsoleCursorPosition(hConsole, screenPos);
    } else {
        std::cerr << "Warning: Could not get console buffer info for clearing screen." << std::endl;
    }
#else
    // ANSI escape code to clear screen and move cursor to home position
    std::cout << "\033[2J\033[1;1H" << std::flush;
#endif
}

WindowSize Console::getWindowSize() const {
    return currentSize;
}

void Console::printLineOfChars(char character, int length) const {
    if (length <= 0) return;
    std::cout << std::string(static_cast<std::string::size_type>(length), character);
}

void Console::printBorder(char borderChar) const {
    // Top border
    printLineOfChars(borderChar, currentSize.width);
    std::cout << '\n';

    // Middle section with side borders
    for (int i = 0; i < currentSize.height - 2; ++i) {
        std::cout << borderChar;
        printLineOfChars(' ', currentSize.width - 2); // Fill with spaces
        std::cout << borderChar << '\n';
    }

    // Bottom border
    printLineOfChars(borderChar, currentSize.width);
    std::cout << '\n';
}

void Console::printCentered(const std::string& text, char borderChar) const {
    if (currentSize.width < 2) { // Not enough space for borders
        std::cout << text << '\n';
        return;
    }

    std::cout << borderChar;
    int contentWidth = currentSize.width - 2;
    if (contentWidth < 0) contentWidth = 0; // Prevent negative width

    int padding = (contentWidth - static_cast<int>(text.length())) / 2;
    int remaining = contentWidth - padding - static_cast<int>(text.length());

    // Print left padding
    printLineOfChars(' ', padding);
    // Print text
    std::cout << text;
    // Print right padding
    printLineOfChars(' ', remaining);
    std::cout << borderChar << '\n';
}

std::string Console::getSystemInfo() const {
    std::string platform;
#if defined(_WIN32)
    #if defined(_WIN64)
        platform = "Windows 64-bit";
    #else
        platform = "Windows 32-bit";
    #endif
#elif defined(__APPLE__)
    platform = "macOS (Apple/Darwin)";
#elif defined(__linux__)
    platform = "Linux";
#elif defined(__FreeBSD__)
    platform = "FreeBSD";
#elif defined(__NetBSD__)
    platform = "NetBSD";
#elif defined(__OpenBSD__)
    platform = "OpenBSD";
#elif defined(__sun) || defined(__sun__)
    platform = "Solaris (SunOS)";
#else
    platform = "Unknown Unix-like Platform";
#endif
    return platform;
}
