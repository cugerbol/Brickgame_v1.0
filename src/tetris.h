#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define FIGURE_SIZE 5
#define HEIGHT_FIELD 12
#define WIDTH_FIELD 10

#define FIGURE_START_Y -5
#define SHIFT_FIELD_X 5
#define SHIFT_FIELD_Y 5

#define TET_PLAYER_RIGHT 'd'
#define TET_PLAYER_LEFT 'a'
#define TET_PLAYER_DOWN 's'
#define TET_PLAYER_NOP ' '

#define COUNT_ITERATION 30

typedef struct TetFigure_t
{
    int **blocks;
    int x;
    int y;

} TetFigure_t;

typedef struct TetPlayer_t
{
    int action;
} TetPlayer_t;

typedef struct TetField_t
{
    int **blocks;
} TetField_t;

typedef struct TetGame_t
{
    TetFigure_t *figure;
    TetFigure_t *figureNext;
    TetPlayer_t *player;
    TetField_t *field;

    int counterIter;
    int action;
    int score;

} TetGame_t;

#endif