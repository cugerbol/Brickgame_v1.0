#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define FIGURE_SIZE 5
#define HEIGHT_FIELD 20
#define WIDTH_FIELD 10

#define FIGURE_START_Y 0
#define SHIFT_FIELD_X 5
#define SHIFT_FIELD_Y 5

#define COUNT_ITERATION 30

typedef struct TetFigure_t
{
    int **blocks;
    int color;
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

typedef enum
{
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action

} UserAction_t;

typedef struct GameInfo_t
{
    int speed;
    int score;
    int record;
    int level;

} GameInfo_t;
;

typedef struct TetGame_t
{
    TetFigure_t *figure;
    TetFigure_t *figureNext;
    TetPlayer_t *player;
    TetField_t *field;
    GameInfo_t *gameInfo;

    int action;
    int counterIter;
    int gameStatus;

} TetGame_t;

#endif