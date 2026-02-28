# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c11 -g
TARGET  = dcl
SRC     = dcl.c
OBJ     = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compile
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(TARGET) $(OBJ)

# Rebuild from scratch
re: clean all

.PHONY: all clean re
