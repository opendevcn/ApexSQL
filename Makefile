# Makefile for ApexSQL project
# Compatible with Linux and Windows

# Directories
SRC = src
INCLUDE = src/.include
LOG = log
BIN = bin

# Target executable
TARGET = $(BIN)/apexsql

# Log file
LOG_FILE = $(LOG)/apexsql-compile-errlog.txt

# Compiler
CXX = g++
CXXFLAGS = -std=c++20 -static

# Find all source files
CPP_FILES = $(shell find $(SRC) -name "*.cpp" -type f)

# Find all header files
HPP_FILES = $(shell find $(INCLUDE) -name "*.hpp" -type f)

# Include directories
INCLUDE_DIRS = $(sort $(dir $(HPP_FILES)))
INCLUDE_FLAGS = $(addprefix -I,$(INCLUDE_DIRS))

# Resource file for Windows
ifeq ($(OS),Windows_NT)
    RESOURCE = tmp/apexsql_resource.o
    RESOURCE_SRC = tmp/apexsql.rc
    WINDRES = windres
else
    RESOURCE = 
endif

# Default target
all: $(TARGET)

# Main target
$(TARGET): $(CPP_FILES) $(HPP_FILES) $(RESOURCE)
	@echo "Compiling ApexSQL project..."
	@$(CXX) $(CXXFLAGS) $(INCLUDE_FLAGS) $(CPP_FILES) $(RESOURCE) -o $@ 2> $(LOG_FILE)
	@if [ $$? -ne 0 ]; then \
		echo "Error: Compilation failed, log details: $(LOG_FILE)"; \
		exit 1; \
	fi
	@echo "Compilation successful! Executable: $(TARGET)"
	@if [ -n "$(RESOURCE)" ] && [ -f "$(RESOURCE)" ]; then \
		rm -f $(RESOURCE); \
		echo "Cleaned up resource files"; \
	fi

# Compile resource file for Windows
$(RESOURCE): $(RESOURCE_SRC)
	@echo "Compiling resource file..."
	@$(WINDRES) $< -o $@ 2> $(LOG_FILE)
	@if [ $$? -ne 0 ]; then \
		echo "Error: Resource compilation failed, log details: $(LOG_FILE)"; \
		exit 1; \
	fi
	@echo "Resource file compiled successfully"

# Clean target
clean:
	@echo "Cleaning up..."
	@if [ -f "$(TARGET)" ]; then \
		rm -f $(TARGET); \
		echo "Removed $(TARGET)"; \
	fi
	@if [ -f "$(RESOURCE)" ]; then \
		rm -f $(RESOURCE); \
		echo "Removed $(RESOURCE)"; \
	fi
	@echo "Clean completed"

# Help target
help:
	@echo "Makefile for ApexSQL project"
	@echo "Compatible with Linux and Windows"
	@echo ""
	@echo "Targets:"
	@echo "  all       - Compile the project"
	@echo "  clean     - Clean up compiled files"
	@echo "  help      - Show this help message"
	@echo ""
	@echo "Directories:"
	@echo "  SRC     = $(SRC)"
	@echo "  INCLUDE = $(INCLUDE)"
	@echo "  LOG     = $(LOG)"
	@echo "  BIN     = $(BIN)"
