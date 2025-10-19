# Game Makefile - Links against Froglib Engine
# Builds the game executable using the Froglib static library

SHELL := /bin/bash

# Compiler
CXX := clang++

# Paths
ENGINE_ROOT := ..
ENGINE_LIB := $(ENGINE_ROOT)/lib/libfroglib.a
ENGINE_INCLUDE := $(ENGINE_ROOT)/include

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -I$(ENGINE_INCLUDE) -Iinclude
DEBUGFLAGS := -g -O0 -DDEBUG
RELEASEFLAGS := -O3 -DNDEBUG

# Raylib linking flags
pkgConfigRaylibFlags := $(shell pkg-config --cflags --libs raylib 2>/dev/null || true)
ifeq ($(strip $(pkgConfigRaylibFlags)),)
    # Fallback linking (Linux-ish). Adapt for your platform if needed.
    LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt
else
    LDFLAGS := $(pkgConfigRaylibFlags)
endif

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

# Find all game source files
SRC_FILES := $(shell find $(SRC_DIR) -name "*.cpp")
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Target executable
TARGET := $(BIN_DIR)/game

# Phony targets
.PHONY: all debug release run clean dirs engine help

# Default target
all: dirs engine $(TARGET)

# Create necessary directories
dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# Build the engine library if it doesn't exist
engine:
	@if [ ! -f $(ENGINE_LIB) ]; then \
		echo "Engine library not found, building it..."; \
		$(MAKE) -C $(ENGINE_ROOT); \
	fi

# Link the executable
$(TARGET): $(OBJ_FILES) $(ENGINE_LIB)
	@echo "Linking game -> $@"
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Game built successfully: $@"

# Compile game source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@echo "Compiling -> $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug build
debug: CXXFLAGS := $(CXXFLAGS) $(DEBUGFLAGS)
debug: clean
	@$(MAKE) -C $(ENGINE_ROOT) debug
	@$(MAKE) all
	@echo "Debug build complete"

# Release build
release: CXXFLAGS := $(CXXFLAGS) $(RELEASEFLAGS)
release: clean
	@$(MAKE) -C $(ENGINE_ROOT) release
	@$(MAKE) all
	@echo "Release build complete"

# Run the game
run: all
	@echo "Running $(TARGET)"
	@./$(TARGET)

# Clean game build artifacts only
clean:
	@echo "Cleaning game build artifacts..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Game clean complete"

# Clean everything including engine
clean-all: clean
	@echo "Cleaning engine..."
	@$(MAKE) -C $(ENGINE_ROOT) clean

bear:
	bear -- $(MAKE) clean
	bear -- $(MAKE)

# Help target
help:
	@echo "Game Makefile"
	@echo "============="
	@echo "Targets:"
	@echo "  all        - Build the game (default)"
	@echo "  debug      - Build game and engine with debug symbols"
	@echo "  release    - Build optimized release version"
	@echo "  run        - Build and run the game"
	@echo "  clean      - Remove game build artifacts"
	@echo "  clean-all  - Remove game and engine build artifacts"
	@echo "  engine     - Build the engine library"
	@echo "  help       - Show this help message"

