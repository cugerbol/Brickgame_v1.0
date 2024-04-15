#ifndef FSM_H
#define FSM_H

#include "tetris.h"

// Функция для просчета одной итерации
void calculateTet(TetGame_t *game);

// Обновляет текущий состояние игры
TetGame_t *updateCurrentState(TetGame_t *game);

// Инициализация игры
void initGame(TetGame_t *game);

#endif