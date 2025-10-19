# Froglib Engine - Static Library Makefile
# Builds the Froglib engine as a static library (libfroglib.a)
# Game projects should link against this library

SHELL := /bin/bash

# Compiler and archiver
CXX := clang++
AR := ar
ARFLAGS := rcs

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Iinclude
DEBUGFLAGS := -g -O0 -DDEBUG
RELEASEFLAGS := -O3 -DNDEBUG

# Raylib flags (for compilation only, not linking - games will handle that)
pkgConfigRaylibCFlags := $(shell pkg-config --cflags raylib 2>/dev/null || true)
ifeq ($(strip $(pkgConfigRaylibCFlags)),)
    RAYLIB_CFLAGS :=
else
    RAYLIB_CFLAGS := $(pkgConfigRaylibCFlags)
endif

# Directories
SRC_DIR := src
BUILD_DIR := build
LIB_DIR := lib
INCLUDE_DIR := include

# Find all .cpp files in src/ recursively
SRC_FILES := $(shell find $(SRC_DIR) -name "*.cpp")
# Create corresponding .o files in build/ mirroring src/ structure
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
# Target library
TARGET_LIB := $(LIB_DIR)/libfroglib.a

# Phony targets
.PHONY: all debug release clean install help

# Default target
all: $(TARGET_LIB)

# Build static library
$(TARGET_LIB): $(OBJ_FILES) | $(LIB_DIR)
	@echo "Creating static library -> $@"
	$(AR) $(ARFLAGS) $@ $^
	@echo "Library built successfully: $@"

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@echo "Compiling -> $<"
	$(CXX) $(CXXFLAGS) $(RAYLIB_CFLAGS) -c $< -o $@

# Create necessary directories
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

# Debug build
debug: CXXFLAGS := $(CXXFLAGS) $(DEBUGFLAGS)
debug: clean all
	@echo "Debug library built"

# Release build
release: CXXFLAGS := $(CXXFLAGS) $(RELEASEFLAGS)
release: clean all
	@echo "Release library built"

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR) $(LIB_DIR)
	@echo "Clean complete"

bear:
	bear -- $(MAKE) clean
	bear -- $(MAKE)

# Install library and headers to system (optional)
install: $(TARGET_LIB)
	@echo "Install target not yet implemented"
	@echo "Manually copy $(TARGET_LIB) and $(INCLUDE_DIR)/* to your desired location"

# Help target
help:
	@echo "Froglib Engine Makefile"
	@echo "======================"
	@echo "Targets:"
	@echo "  all      - Build the engine library (default)"
	@echo "  debug    - Build with debug symbols"
	@echo "  release  - Build optimized release version"
	@echo "  clean    - Remove all build artifacts"
	@echo "  install  - Install library and headers (not implemented)"
	@echo "  help     - Show this help message"

