CC = gcc
CFLAGS = -Wall -Wextra -Werror

# other libs may specify here
# INC_ARR = ../some_lib
# INCLUDE_LIBS = $(INC_ARR)
# CFLAGS += -I$(INCLUDE_LIBS)

SRCS = $(wildcard *.c) # $(INC_ARR)/some_lib_sources.c
OBJS = $(patsubst %.c, %.o, $(SRCS))
TARGET = test_deque

all: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

valgrind_check: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)