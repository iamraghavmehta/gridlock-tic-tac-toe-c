CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
TARGET = gridlock.exe
SRC = src/game.c src/main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o

run: $(TARGET)
	./$(TARGET)
