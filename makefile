C_SRCS = ladd.c
CXX_SRCS = calc.cpp

C_OBJS = $(C_SRCS:.c=.o)
CXX_OBJS = $(CXX_SRCS:.cpp=.o)

LIB = libladd.so
BIN = Calc

CFLAGS = -fPIC -Wall -g -pthread
CXXFLAGS = -fPIC -Wall -g -pthread

all: $(BIN)

$(BIN): $(CXX_OBJS)
	g++ $(CXXFLAGS) -o $@ $^ -ldl

//$(LIB): $(C_OBJS)
	// gcc $(CFLAGS) -shared -o $@ $^



%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(C_OBJS) $(CXX_OBJS) $(LIB) $(BIN)
