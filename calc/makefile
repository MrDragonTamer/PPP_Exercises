# Project settings
PROJECT_NAME := $(notdir $(CURDIR))
SRC_DIR := src
INC_DIR := include
OBJ_DIR := build/obj
BIN_DIR := build/bin
MODULE_DIR := $(SRC_DIR)/modules
CC := g++
CFLAGS := -std=c++23 -fmodules -Wall -Wextra -Werror -I$(INC_DIR)
MODULE_FLAGS := $(CFLAGS)

# Find all .cpp files in src/
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Define all required modules

MODULES :=./gcm.cache/PPP.gcm
STD_MODULE := ./gcm.cache/std.gcm

# Final executable
TARGET := $(BIN_DIR)/$(PROJECT_NAME)

# Default target
all: $(MODULES) $(TARGET) | $(STD_MODULE)


# Rule for compiling modules
./gcm.cache/%.gcm: $(MODULE_DIR)/%.cxx | $(STD_MODULE)
	g++ $(MODULE_FLAGS) -c -fmodule-only $<

#Rule for compiling the std module
$(STD_MODULE):
	#g++ -fmodules -std=c++23 -fsearch-include-path bits/std.cc -c -fmodule-only
	g++ $(MODULE_FLAGS) -fsearch-include-path bits/std.cc -c -fmodule-only

# Link the executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -r gcm.cache/
	rm -r build/
	mkdir -p build/

# Phony targets
.PHONY: all clean

