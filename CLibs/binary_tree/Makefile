CC = clang
CFLAGS = -Wall -Wextra -Werror

# other libs may specify here
# INC_ARR = ../some_lib
# INCLUDE_LIBS = $(INC_ARR)
# CFLAGS += -I$(INCLUDE_LIBS)

SRCS = $(filter-out test*.c, $(wildcard bin_tree*.c))
OBJS = $(patsubst %.c, %.o, $(SRCS))

TEST_SRCS = test4.c
TEST_OBJS = $(patsubst %.c, %.o, $(TEST_SRCS))

TARGET = bin_tree_test

all: build_lib build_test   

build_lib: $(OBJS)

build_test: $(TEST_OBJS) $(OBJS)
	$(CC) $(TEST_OBJS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

valgrind_check: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

test: build_test
	time ./$(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET)