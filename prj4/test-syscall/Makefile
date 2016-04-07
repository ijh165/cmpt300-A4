#  Filename: Makefile
#  Created by Ivan Jonathan Hoo
#  Copyright (c) 2016 Ivan Jonathan Hoo. All rights reserved.

TARGET = cs300_testapp
OBJS = cs300_testapp.o

CFLAGS = -std=c99 -g -Wall -Werror -D _GNU_SOURCE -static
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
	scp -P 2222 $(TARGET) root@localhost:$~

killqemu:
	killall qemu-system-x86_64