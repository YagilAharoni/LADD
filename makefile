# C++ Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I./

# C Compiler
CC = gcc
# -fPIC is needed for the shared library
CFLAGS = -std=c11 -Wall -I./ -fPIC

# Linker flags for the C++ executable
# -L. tells the linker to look in the current directory
# -lladd tells the linker to link against 'libladd.so'
# -Wl,-rpath,. embeds the runtime search path
LDFLAGS = -L. -lladd -Wl,-rpath,.

# Target names
TARGET_EXEC = calc
TARGET_LIB = libladd.so

# Source files
# Note: Using .c for the library source
EXEC_SRC = calc.cpp
LIB_SRC = ladd/ladd.c

# Object files
EXEC_OBJ = $(EXEC_SRC:.cpp=.o)
LIB_OBJ = $(LIB_SRC:.c=.o)

# Default target: build the executable
all: $(TARGET_EXEC)

# Rule to build the executable (using C++ linker)
$(TARGET_EXEC): $(EXEC_OBJ) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) -o $(TARGET_EXEC) $(EXEC_OBJ) $(LDFLAGS)

# Rule to build the shared library (using C linker)
$(TARGET_LIB): $(LIB_OBJ)
	$(CC) -shared -o $(TARGET_LIB) $(LIB_OBJ)

# Rule to compile the C++ executable's object file
$(EXEC_OBJ): $(EXEC_SRC)
	$(CXX) $(CXXFLAGS) -c $(EXEC_SRC) -o $(EXEC_OBJ)

# Rule to compile the C library's object file
$(LIB_OBJ): $(LIB_SRC)
	$(CC) $(CFLAGS) -c $(LIB_SRC) -o $(LIB_OBJ)

# Clean target
clean:
	rm -f $(EXEC_OBJ) $(LIB_OBJ) $(TARGET_EXEC) $(TARGET_LIB)