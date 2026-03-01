# ==========================================
#   Settings
# ==========================================

# Name of your final executable
TARGET_NAME := image-viewer

# --- SDL2 CONFIGURATION ---
# usage of "shell" command gets the flags directly from the system
SDL_CFLAGS := $(shell pkg-config --cflags sdl3)
SDL_LIBS   := $(shell pkg-config --libs sdl3)

# Compiler settings
CC       := gcc
CXX      := g++
CFLAGS   := -Wall -Wextra -O2 -g $(SDL_CFLAGS)
CXXFLAGS := -Wall -Wextra -O2 -std=c++17 -g $(SDL_CFLAGS)
LDFLAGS  := $(SDL_LIBS)

# Directories
SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := obj

# ==========================================
#   Automatic Detection
# ==========================================

# Final Binary Path
TARGET := $(BIN_DIR)/$(TARGET_NAME)

# Find all source files in the src directory
SRCS_C   := $(wildcard $(SRC_DIR)/*.c)
SRCS_CXX := $(wildcard $(SRC_DIR)/*.cpp)

# Generate object file paths (stripping the src/ prefix and adding obj/)
OBJS_C   := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS_C))
OBJS_CXX := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS_CXX))
OBJS     := $(OBJS_C) $(OBJS_CXX)

# Define the Linker
LINKER   := $(CXX)

# ==========================================
#   Rules
# ==========================================

.PHONY: all clean directories run

all: directories $(TARGET)

# Create the directories
directories:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

# Link the executable safely
$(TARGET): $(OBJS)
	@echo "Linking $@"
	# 1. Link to a temporary file (.tmp) instead of the final target
	@$(LINKER) $(OBJS) $(LDFLAGS) -o $@.tmp
	# 2. If the line above succeeded, rename .tmp to the real name
	@mv -f $@.tmp $@
	@echo "Build successful! Run with: ./$(BIN_DIR)/$(TARGET_NAME)"

# Compile C source files
# Note: Syntax is (Object path): (Source path)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	@echo "Cleaning up..."
	@rm -rf $(BIN_DIR) $(OBJ_DIR)

# Convenience rule to run the program immediately
run: all
	@echo "Running $(TARGET)..."
	@./$(TARGET)
