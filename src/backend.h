#ifndef BACKEND_H
#define BACKEND_H

#include "tetris.h"

// Создать фигуру заполненную нулями
TetFigure_t *createFigure();

// Освободить выделенную для фигуры память
void freeFigure(TetFigure_t *figure);

// Создать поле размером HEIGHT_FIELD на WIGHT_FIELD заполненное нулями
TetField_t *createField();

// Освободить выделенную для поля память
void freeField(TetField_t *field);

// Создать игру
TetGame_t *createGame();

// Освободить выделенную для игры память
void freeGame(TetGame_t *game);

// Создать фигуру из паттернов
TetFigure_t *createRandomFigure();

// Движение фигуры по Y вниз
void moveFigureDown(TetFigure_t *figure);

// Движение фигуры по Y вверх
void moveFigureUp(TetFigure_t *figure);

// Движение фигуры по X влево
void moveFigureLeft(TetFigure_t *figure);

// Движение фигуры по X вправо
void moveFigureRight(TetFigure_t *figure);

// Выкинуть новую фигуру
void updateFigure(TetGame_t *game);

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

#endif