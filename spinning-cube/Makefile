# ==========================================
#   Settings
# ==========================================

# Your new target executable name
TARGET_NAME := cube

# Compiler settings for pure C
CC       := gcc
CFLAGS   := -Wall -Wextra -O2 -g
LDFLAGS  := 

# --- SDL2 CONFIGURATION ---
# The $(shell ...) command in Make acts exactly like `backticks` in your terminal
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LIBS   := $(shell sdl2-config --libs)

# Append SDL flags
# CFLAGS handles the headers during compilation
CFLAGS  += $(SDL_CFLAGS)
# LDFLAGS handles the libraries during linking
LDFLAGS += $(SDL_LIBS)

# Directories
SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := obj

# ==========================================
#   Automatic Detection
# ==========================================

TARGET := $(BIN_DIR)/$(TARGET_NAME)

# Look for C files only
SRCS_C := $(wildcard $(SRC_DIR)/*.c)
OBJS_C := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS_C))

# ==========================================
#   Rules
# ==========================================

.PHONY: all clean directories run

all: directories $(TARGET)

directories:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

# Safe Link-then-Move Rule
# Notice how $(LDFLAGS) comes AFTER $(OBJS_C), just like your terminal command
$(TARGET): $(OBJS_C)
	@echo "Linking $@"
	@$(CC) $(OBJS_C) $(LDFLAGS) -o $@.tmp
	@mv -f $@.tmp $@
	@echo "Build successful! Run with: ./$(BIN_DIR)/$(TARGET_NAME)"

# Compile C source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	@rm -rf $(BIN_DIR) $(OBJ_DIR)
	@rm -f $(TARGET).tmp

run: all
	@echo "Running $(TARGET)..."
	@./$(TARGET)
