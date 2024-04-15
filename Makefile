TARGET = tetris
CC = gcc
CFLAGS = -std=c99 

SRC = src/*.c
OBJ = *.o

all: clean $(TARGET)
	./$(TARGET)

$(TARGET): 
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lncurses 


clean:
	rm -f $(TARGET) $(OBJ)
