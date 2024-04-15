#ifndef FSM_H
#define FSM_H

#include "tetris.h"

// Проверяет находится ли блок в пределах игрового поля
int checkBoundaries(int row, int col, int fy, int fx);

// Проверка столкновения фигуры
int collisionFigure(TetGame_t *game);

// Установить фигуру на поле
void placeFigure(TetGame_t *game);

// Проверяет заполнена ли линия под индексом row
int lineIsFill(TetField_t *field, int row);

// Удаляет строку
void dropLine(TetField_t *field, int row);

// Удаляет строки и подсчитывает результат
int eraseLines(TetGame_t *game);

// Функция для просчета одной итерации
void calculateTet(TetGame_t *game);
#endif