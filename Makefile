# Makefile for Console Utility Project

# Compiler selection
CXX       := g++      # Change to clang++ to use Clang
CXXFLAGS  := -std=c++17 -Wall -Wextra -O2 -m64
INCLUDES  := -Iinclude
SRC_DIR   := src
BUILD_DIR := build
TARGET    := $(BUILD_DIR)/console_app

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Link the final binary
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Run the app
run: all
	./$(TARGET)

.PHONY: all clean run
