#ifndef BONUS_H
#define BONUS_H

#include "tetris.h"

// Увеличение уровня в зависимости от score
void levelUp(TetGame_t *game);

// Переводит кол-во уничтоженных уровней (строк) в score
int converterScore(int count_rows);

// Читает из базы данных максимальный score
int readDataBase();

// Записывает в базу данных максимальный score
int writeDataBase(int score);

#endif