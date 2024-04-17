#ifndef FRONTEND_H
#define FRONTEND_H

#include "tetris.h"
#include <ncurses.h>

#define WHITE 1
#define GREEN 2
#define BLUE 3
#define RED 4
#define CYAN 5
#define MAGNETA 6

typedef struct TetWindows_t
{
    WINDOW *winField;
    WINDOW *winFigure;
    WINDOW *winInfo;
    WINDOW *winButtons;

} TetWindows_t;

// Вывести фигуру на поле с учетом смещения по оси X и Y
void outputFigure(TetFigure_t *figure, WINDOW *win);

// Вывести на экран поле
void outputField(TetField_t *field, WINDOW *win);

// Очистить все символы в координатах
void cleanSymbols(WINDOW *win, int size_y, int size_x);

// Выводит информацию о игре
void ouputInfoGame(TetGame_t *game);

// Инициализирует окна
TetWindows_t *createWindows();

// Вывод всех объектов игры
void frontend(TetGame_t *game, TetWindows_t *winTet);

#endif