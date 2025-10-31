CC = gcc
CFLAGS = -Wall -Wextra -Werror -O1

INC_ARR = ../array

INCLUDE_LIBS = $(INC_ARR)
CFLAGS += -I$(INCLUDE_LIBS)

SRCS = $(wildcard *.c) $(INC_ARR)/array.c
OBJS = $(patsubst %.c, %.o, $(SRCS))
TARGET = test_multiset

all: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

valgrind_check: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)