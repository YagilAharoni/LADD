# Compilers
CC  = gcc
CXX = g++

# Flags
CFLAGS   = -Wall -fPIC -I./
CXXFLAGS = -std=c++11 -Wall -I./
LDFLAGS  = -L. -Wl,-rpath,. -lladd

# Targets
TARGET_EXEC = calc
TARGET_LIB  = libladd.so

# Source files
EXEC_SRC = calc.cpp
LIB_SRC  = ladd/ladd.c

# Object files
EXEC_OBJ = $(EXEC_SRC:.cpp=.o)
LIB_OBJ  = $(LIB_SRC:.c=.o)

# Default target
all: $(TARGET_LIB) $(TARGET_EXEC)

# Rule to build the executable (C++)
$(TARGET_EXEC): $(EXEC_OBJ) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) -o $@ $(EXEC_OBJ) $(LDFLAGS)

# Rule to build the shared library (C)
$(TARGET_LIB): $(LIB_OBJ)
	$(CC) -shared -o $@ $(LIB_OBJ)

# Compile rule for main C++ file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Explicit rule for the C source inside ladd/
ladd/%.o: ladd/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(EXEC_OBJ) $(LIB_OBJ) $(TARGET_EXEC) $(TARGET_LIB)
