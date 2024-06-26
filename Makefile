TARGET = tetris
CC = gcc
CFLAGS = -std=c99 
TEST_FLAGS = -std=c11 -g `pkg-config --cflags --libs check`

SRC = src/brick_game/tetris/*.c 
GUI = src/gui/*.c
OBJ = *.o
TEST = ./tests/tests.c
TEST_PATH = ./tests/
MAIN= src/brick_game/main.c

OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
	OPEN_CMD = xdg-open
else
	CHECK_FLAGS = -lcheck
	OPEN_CMD = open
endif

all: clean install
	./$(TARGET) 


create_tests:
	checkmk clean_mode=1 $(TEST_PATH)*.check >$(TEST_PATH)tests.c 


gcov_report: clean test
	$(CC) $(CFLAGS) $(TEST_FLAGS) -fprofile-arcs -ftest-coverage $(OBJ) $(TEST) -o test -lncurses $(CHECK_FLAGS) $(GCOVFLAGS)
	lcov -t test -o rep.info -c -d .
	genhtml rep.info --output-directory report
	genhtml -o report rep.info 
	$(OPEN_CMD) ./report/index.html
	rm -f *.gcno *.info *.gcda 



test: clean  backend.o create_tests
	$(CC) $(CFLAGS) $(TEST_FLAGS) -fprofile-arcs -ftest-coverage $(SRC) $(TEST) -o test -lncurses $(CHECK_FLAGS) $(GCOVFLAGS)
	./test
	



install: backend.o frontend.o
	$(CC) $(CFLAGS) -o $(TARGET) *.o $(MAIN) -lncurses
	rm -rf *.o



backend.a: backend.o
	ar rcs $(TARGET).a *.o
	ranlib $(TARGET).a


backend.o: 
	$(CC) $(CFLAGS) -c $(SRC)


frontend.o: 
	$(CC) $(CFLAGS) -c $(GUI)


uninstall: clean


check: install
	leaks -atExit -- ./$(TARGET) 


clean:
	rm -f $(TARGET) $(OBJ) a.out
	rm -f *.gcno *.info *.gcda 
	rm -rf report
	rm -f test 
	rm -rf test.dSYM
	

.PHONY: backend.o frontend.o
