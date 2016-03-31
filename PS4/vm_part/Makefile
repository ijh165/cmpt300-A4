# Makefile for building multi-file application
# by Brian Fraser

# final executable to build:
TARGET= fibonacci
# .o files to link in (for all .c files)
OBJS = fibonacci.o


CFLAGS = -Wall -g -std=c99 -Werror -pthread -static -lrt
CC_C = gcc

all: clean $(TARGET)

%.o : %.c
	$(CC) -c $(CFLAGS) $<

$(TARGET): $(OBJS)
	$(CC_C) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
