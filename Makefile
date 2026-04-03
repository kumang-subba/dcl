# Compiler and flags
CC      = gcc
CFLAGS  = -Iinclude -std=c11 -g
TARGET  = dcl
SRCS     = src/dcl.c \
					 src/tokenizer.c \
					 src/common.c		 \
					 src/buffer.c
OBJ     = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(TARGET) $(OBJ)

# Rebuild from scratch
re: clean all

.PHONY: all clean re
