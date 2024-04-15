#ifndef FRONTEND_H
#define FRONTEND_H

#include "tetris.h"

// Вывести фигуру на поле с учетом смещения по оси X и Y
void outputFigure(TetFigure_t *figure, char symb, int shift_y, int shift_x);

// Вывести на экран поле
void outputField(TetField_t *field);

// Очистить все символы в координатах
void cleanSymbols(int y, int x, int size_y, int size_x);

// Выводит информацию о игре
void ouputInfoGame(TetGame_t *game);

// Вывод всех объектов игры
void frontend(TetGame_t *game);

#endif