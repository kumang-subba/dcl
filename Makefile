# Compiler and flags
CC      = gcc
CFLAGS  = -Iinclude -std=c11 -g
TARGET  = dcl
SRCS     = src/dcl.c \
					 src/tokenizer.c \
					 src/common.c		 \
					 src/buffer.c
OBJS     = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

# Clean build files
clean:
	rm -f $(TARGET) $(OBJS)

# Rebuild from scratch
re: clean all

.PHONY: all clean re
