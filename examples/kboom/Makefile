CC = gcc
LIBS = -lgmp

CFLAGS  = -std=c17
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror
CFLAGS += -Wmissing-declarations

###
CXX = g++
TLIBS =  -lgtest
TLIBS += -lgtest_main
TLIBS += -pthread

CXXFLAGS = -std=c++23
CXXFLAGS += -ggdb
CXXFLAGS += -Wall
CXXFLAGS += -Weffc++
CXXFLAGS += -Wextra
CXXFLAGS += -Wconversion
CXXFLAGS += -Wsign-conversion
CXXFLAGS += -pedantic
CXXFLAGS += -pedantic-errors
CXXFLAGS += -Werror
CXXFLAGS += -Wmissing-declarations

# Sources
MAIN_SRC := main.c
MAIN_OBJ := $(MAIN_SRC:.c=.o)
SRCS := $(filter-out $(MAIN_SRC), $(wildcard *.c))
OBJS := $(SRCS:.c=.o)

# Test Sources
TEST_SRCS := $(wildcard *.test.cpp)
TEST_OBJS := $(TEST_SRCS:.cpp=.o)

.PHONY: all
all: main.out

.PHONY: test
test: test.out
	@echo "Running tests..."
	@./test.out

main.out: $(OBJS) $(MAIN_OBJ)
	@echo Linking $@
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	@echo Compiling $<
	@$(CC) $(CFLAGS) -c $< -o $@

test.out: $(TEST_OBJS) $(OBJS)
	@echo Linking $@
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(TLIBS)

%.test.o: %.test.cpp
	@echo Compiling test $<
	@$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: run
run: main.out
	@./main.out $(ARGS)

.PHONY: clean
clean:
	rm -f *.o *.out *.out.dSYM *.test.o test.out
