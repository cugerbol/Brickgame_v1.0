TARGET = tetris
CC = gcc
CFLAGS = -std=c99 

SRC = src/*.c
OBJ = *.o

all: clean $(TARGET)
	./$(TARGET)

$(TARGET): 
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lncurses 


build: clean $(TARGET)

check: build
	leaks -atExit -- ./tetris

clean:
	rm -f $(TARGET) $(OBJ)


