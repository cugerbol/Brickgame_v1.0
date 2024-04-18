TARGET = tetris
CC = gcc
CFLAGS = -std=c99 
TEST_PATH = ./tests/
TEST_FLAGS = -std=c11 -g `pkg-config --cflags --libs check`

SRC = src/brick_game/tetris/*.c src/gui/*.c
OBJ = *.o

all: clean $(TARGET)
	./$(TARGET)

$(TARGET): 
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lncurses 


build: clean $(TARGET)


create_tests:
	checkmk clean_mode=1 $(TEST_PATH)*.check >$(TEST_PATH)tests.c 

	


check: build
	leaks -atExit -- ./tetris

clean:
	rm -f $(TARGET) $(OBJ)


