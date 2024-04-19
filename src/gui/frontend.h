#ifndef FRONTEND_H
#define FRONTEND_H

#include "../brick_game/tetris/tetris.h"
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

// Вывести фигуру на поле
void outputFigure(TetFigure_t *figure, WINDOW *win);

// Вывести на экран поле
void outputField(TetField_t *field, WINDOW *win);

// Очистить все символы в координатах
void cleanSymbols(WINDOW *win, int size_y, int size_x);

// Выводит информацию о игре
void ouputInfoGame(TetGame_t *game, WINDOW *win);

// Выводит окно кнопок
void outputButtons(WINDOW *win);

// Инициализирует окна
TetWindows_t *createWindows();

// Освободить память окон
void freeWindows(TetWindows_t *winTet);

// Выводит GAME OVER
void outpuGameOver(WINDOW *win, TetGame_t *game);

// Вывод всех объектов игры
void frontend(TetGame_t *game, TetWindows_t *winTet);

// Главная функция отвечающая ща GUI
TetWindows_t *tetrisGUI();

#endif