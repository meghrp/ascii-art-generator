# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lm

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Source files
SOURCES = $(SRC_DIR)/main2.c $(SRC_DIR)/image.c
OBJECTS = $(BUILD_DIR)/main2.o $(BUILD_DIR)/image.o

# Target executable
TARGET = main

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build target executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Rebuild everything
rebuild: clean all

# Phony targets
.PHONY: all clean rebuild

# Dependencies
$(BUILD_DIR)/main2.o: $(SRC_DIR)/main2.c $(INCLUDE_DIR)/image.h
$(BUILD_DIR)/image.o: $(SRC_DIR)/image.c $(INCLUDE_DIR)/image.h $(INCLUDE_DIR)/stb_image.h

