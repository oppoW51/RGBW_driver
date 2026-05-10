CC ?= gcc
CFLAGS ?= -Wall -Wextra -Werror -std=c99 -IInc

SRCS = $(wildcard Src/*.c) 
OBJS = $(SRCS:.c=.o)

all: rgbw_driver

rgbw_driver: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) rgbw_driver

.PHONY: all clean
