# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -I./

# Flags for building Position Independent Code (needed for shared library)
PICFLAGS = -fPIC

# Linker flags for the executable
LDFLAGS = -L. -lladd -Wl,-rpath,.

# Target names
TARGET_EXEC = calc
TARGET_LIB = libladd.so

# Source files
# ---> This is the fix: Look for ladd.cpp
EXEC_SRC = calc.cpp
LIB_SRC = ladd/ladd.cpp

# Object files
EXEC_OBJ = $(EXEC_SRC:.cpp=.o)
LIB_OBJ = $(LIB_SRC:.cpp=.o)

# Default target: build the executable
all: $(TARGET_EXEC)

# Rule to build the executable
$(TARGET_EXEC): $(EXEC_OBJ) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) -o $(TARGET_EXEC) $(EXEC_OBJ) $(LDFLAGS)

# Rule to build the shared library
$(TARGET_LIB): $(LIB_OBJ)
	$(CXX) -shared -o $(TARGET_LIB) $(LIB_OBJ)

# Rule to compile the executable's object file
$(EXEC_OBJ): $(EXEC_SRC)
	$(CXX) $(CXXFLAGS) -c $(EXEC_SRC) -o $(EXEC_OBJ)

# Rule to compile the library's object file (with -fPIC)
$(LIB_OBJ): $(LIB_SRC)
	$(CXX) $(CXXFLAGS) $(PICFLAGS) -c $(LIB_SRC) -o $(LIB_OBJ)

# Clean target
clean:
	rm -f $(EXEC_OBJ) $(LIB_OBJ) $(TARGET_EXEC) $(TARGET_LIB)