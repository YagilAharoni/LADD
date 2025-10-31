# Compilers
CC  = gcc
CXX = g++

# Flags
CFLAGS   = -Wall -I./
CXXFLAGS = -std=c++11 -Wall -I./

# Target
TARGET_EXEC = FileReader

# Source files
EXEC_SRC = filereader.cpp
LIB_SRC  = ladd.c

# Object files
EXEC_OBJ = $(EXEC_SRC:.cpp=.o)
LIB_OBJ  = $(LIB_SRC:.c=.o)

# Default target
all: $(TARGET_EXEC)

# Build executable (link all objects together)
$(TARGET_EXEC): $(EXEC_OBJ) $(LIB_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(EXEC_OBJ) $(LIB_OBJ)

# Compile C++ files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C files
ladd.o: ladd.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(EXEC_OBJ) $(LIB_OBJ) $(TARGET_EXEC)
