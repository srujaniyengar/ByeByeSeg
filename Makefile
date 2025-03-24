
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -Iinclude
TARGET = example
SRC = src/safealloc.c src/memLock.c example/example.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

example/%.o: example/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

