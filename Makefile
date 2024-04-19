TARGET = tetris
CC = gcc
CFLAGS = -std=c99 
TEST_PATH = ./tests/
TEST_FLAGS = -std=c11 -g `pkg-config --cflags --libs check`

SRC = src/brick_game/tetris/*.c src/gui/*.c
OBJ = *.o


OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
	OPEN_CMD = open
else
	CHECK_FLAGS = -lcheck
	OPEN_CMD = xdg-open
endif


all: clean $(TARGET)
	./$(TARGET)






$(TARGET): 
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lncurses 


build: clean $(TARGET)


create_tests:
	checkmk clean_mode=1 $(TEST_PATH)*.check >$(TEST_PATH)tests.c 



#install, uninstall, clean, dvi, dist, test, gcov_report.

check: build
	leaks -atExit -- ./tetris

clean:
	rm -f $(TARGET) $(OBJ)


