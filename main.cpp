// File: main.cpp
// Author: Gregory K. Bowne
// Date: July 30, 2025
// Brief: This program demonstrates console manipulation using the Console class,
//        calculating and displaying console size, clearing the screen,
//        and presenting system information within a bordered display.

#include "../include/Console.h" // Include our custom Console class header
#include <stdexcept>   // For std::exception
#include <chrono>      // For std::chrono::seconds
#include <thread>      // For std::this_thread::sleep_for

int main() {
    try {
        Console console; // Create an instance of the Console class

        console.clearScreen(); // Clear the console

        WindowSize size = console.getWindowSize(); // Get current console dimensions

        // Print the border (using 'X' as default)
        console.printBorder();

        // Print information centered within the border
        console.printCentered("Console Information:", '#');
        console.printCentered("Width: " + std::to_string(size.width), '#');
        console.printCentered("Height: " + std::to_string(size.height), '#');
        console.printCentered("System: " + console.getSystemInfo(), '#');
        console.printCentered("", '#'); // Empty line for spacing

        // Fill remaining lines with empty centered lines or specific content
        // We've already printed 6 lines (top border, 4 info lines, bottom border).
        // The printBorder handles the initial height - 2 for inner lines.
        // We need to fill the space *within* the border that's not taken by info.
        int linesUsedForInfo = 5; // Console Information, Width, Height, System, empty line
        int linesAvailableForFilling = size.height - 2 - linesUsedForInfo;

        if (linesAvailableForFilling > 0) {
            console.printCentered("--- More Content Here ---", '#');
            linesAvailableForFilling--; // Decrement as we used one more line
        }

        // Fill any remaining space with a simple message
        for (int i = 0; i < linesAvailableForFilling; ++i) {
            console.printCentered("Filling space...", '#');
        }

        // Final print to ensure border is correct.
        // The printBorder() function already prints the top and bottom borders and the side borders.
        // The issue with the old code was how it tried to fill space *after* calling printBorder,
        // which already drew the entire border including the bottom one.

        // To properly use the border and fill, we would modify printBorder to take content lines,
        // or draw the border manually line by line and insert content.
        // For simplicity with the current `printBorder` function, we'll just demonstrate it as is,
        // then clear and demonstrate filling within the borders in a more controlled manner.

        std::cout << "\n\nPress Enter to see content within a dynamically drawn border...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Wait for user input

        console.clearScreen();
        size = console.getWindowSize(); // Re-get size in case window changed

        // Dynamic content drawing within a border
        char dynamicBorderChar = '=';
        int currentLine = 0; // Track current line for drawing

        // Top border
        console.printLineOfChars(dynamicBorderChar, size.width);
        std::cout << '\n';
        currentLine++;

        // Content lines
        std::string welcomeMessage = "Welcome to the Console Utility!";
        std::string instructions = "Resize this window to see changes!";
        std::string goodbye = "Exiting in 5 seconds...";

        // Print welcome message
        console.printCentered(welcomeMessage, dynamicBorderChar);
        currentLine++;

        // Print instructions
        console.printCentered(instructions, dynamicBorderChar);
        currentLine++;

        // Print empty line
        console.printCentered("", dynamicBorderChar);
        currentLine++;

        // Print another centered message
        console.printCentered("Current Time: " + std::to_string(std::time(nullptr)), dynamicBorderChar);
        currentLine++;

        // Calculate remaining lines before the bottom border
        int linesToFillBeforeBottom = size.height - 2 - currentLine;

        // Fill remaining lines with spaces or generic content
        if (linesToFillBeforeBottom > 0) {
            for (int i = 0; i < linesToFillBeforeBottom; ++i) {
                if (i == linesToFillBeforeBottom / 2) {
                    console.printCentered(goodbye, dynamicBorderChar);
                } else {
                    console.printCentered("", dynamicBorderChar); // Empty line within border
                }
            }
            currentLine += linesToFillBeforeBottom;
        }

        // Bottom border
        console.printLineOfChars(dynamicBorderChar, size.width);
        std::cout << '\n';
        currentLine++;

        // Wait before exiting
        std::this_thread::sleep_for(std::chrono::seconds(5));

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
