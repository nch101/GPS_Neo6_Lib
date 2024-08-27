# Target name
TARGET = test

# Build directory
BUILD_DIR = build

# C sources
C_SOURCES = \
Src/Neo6M_GPSNeo6M.c

# Cpp sources
CPP_SOURCES = \
Test/Src/Neo6M_GPSNeo6M_Test.cpp

# Include directories
INCLUDES = \
-IInc \
-ITest/Inc

# Libraries
ifeq ($(OS), Windows_NT)
	LIBS_PATH = Test/Lib/Windows
else ifeq ($(shell uname), Linux)
	LIBS_PATH = Test/Lib/Linux
endif

LIBS = -lgtest -lgtest_main

# Compiler and flags
CC = gcc
CXX = g++

CFLAGS = -Wall -g -O0

ifeq ($(OS), Windows_NT)
	RMDIR = rmdir /s /q
else ifeq ($(shell uname), Linux)
	RMDIR = rm -rf
endif

# List of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
# Search path for c sources
vpath %.c $(sort $(dir $(C_SOURCES)))

# List of objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.o)))
# Search path for cpp sources
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

# Default action: all 
.PHONY: all build clean check memcheck

all:
	@make clean -s -i
	@make build --no-print-directory
	@make check --no-print-directory
	@make memcheck --no-print-directory

build: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/%.o: %.c
	mkdir $(BUILD_DIR)
	$(CC) -c $(INCLUDES) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) -c $(INCLUDES) $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -L$(LIBS_PATH) $(LIBS) -o $@

check:
	./$(BUILD_DIR)/$(TARGET) --gtest_color=yes

memcheck:
	valgrind	--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				--verbose \
				build/test > /dev/null

clean: 
	@$(RMDIR) $(BUILD_DIR)
