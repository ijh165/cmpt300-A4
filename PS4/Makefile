#  Filename: Makefile
#  Created by Ivan Jonathan Hoo
#  Copyright (c) 2016 Ivan Jonathan Hoo. All rights reserved.

TARGET= fibonacci
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

transfer:
	scp -P 2222 $(TARGET) root@localhost:$(TARGET)

killqemu:
	killall qemu-system-x86_64