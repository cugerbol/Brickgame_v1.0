#ifndef FSM_C
#define FSM_C

#include "tetris.h"
#include "backend.h"
#include "fsm.h"

// Проверяет находится ли блок в пределах игрового поля
int checkBoundaries(int row, int col, int fy, int fx)
{
    int result = 1;
    if ((row + fy > HEIGHT_FIELD || row + fy < 0) ||
        (col + fx > WIDTH_FIELD - 1 || col + fx < 0))
        result = 0;
    return result;
}

// Проверка столкновения фигуры
int collisionFigure(TetGame_t *game)
{
    int result = 0;

    int fx = game->figure->x;
    int fy = game->figure->y;

    int **figure = game->figure->blocks;
    int **field = game->field->blocks;

    for (int row = 0; row < FIGURE_SIZE; row++)
    {
        for (int col = 0; col < FIGURE_SIZE; col++)
        {
            int fgr = figure[row][col];

            if (fgr == 1)
            {
                if (checkBoundaries(row, col, fy + 1, fx))
                {
                    int fld = field[fy + row][fx + col];

                    if (fgr != 0 && fld != 0)
                    {
                        result = 1;
                        break;
                    }
                }

                if (!checkBoundaries(row, col, fy + 1, fx))
                {
                    result = 1;
                    break;
                }
            }
        }
        if (result)
            break;
    }

    return result;
}

// Установить фигуру на поле
void placeFigure(TetGame_t *game)
{
    int fy = game->figure->y;
    int fx = game->figure->x;

    for (int row = 0; row < FIGURE_SIZE; row++)
    {
        for (int col = 0; col < FIGURE_SIZE; col++)
        {
            int fgr = game->figure->blocks[row][col];
            if (fgr != 0)
            {
                game->field->blocks[fy + row][fx + col] = fgr;
            }
        }
    }
}

// Проверяет заполнена ли линия под индексом row
int lineIsFill(TetField_t *field, int row)
{
    int result = 1;
    for (int col = 0; col < WIDTH_FIELD; col++)
    {
        int block = field->blocks[row][col];
        if (block == 0)
            result = 0;
    }
    return result;
}

// Удаляет строку
void dropLine(TetField_t *field, int row)
{
    if (row == HEIGHT_FIELD)
    {
        for (int col = 0; col < WIDTH_FIELD; col++)
            field->blocks[row][col] = 0;
    }
    else
    {
        for (int i = row; i > 0; i--)
        {
            for (int col = 0; col < WIDTH_FIELD; col++)
            {
                field->blocks[i][col] = field->blocks[i - 1][col];
            }
        }
    }
}

// Удаляет строки и подсчитывает результат
int eraseLines(TetGame_t *game)
{
    int counter = 0;
    for (int row = HEIGHT_FIELD - 1; row >= 0; row--)
    {
        while (lineIsFill(game->field, row))
        {
            dropLine(game->field, row);
            counter++;
        }
    }
    return counter;
}

// Функция для просчета одной итерации
void calculateTet(TetGame_t *game)
{
    if (game->counterIter == COUNT_ITERATION)
    {
        game->counterIter = 0;
        moveFigureDown(game->figure);

        if (collisionFigure(game))
        {
            moveFigureUp(game->figure);
            placeFigure(game);
            game->score += eraseLines(game);
            updateFigure(game);
        }
    }
    else
    {
        switch (game->action)
        {
        case TET_PLAYER_RIGHT:
        {
            moveFigureRight(game->figure);
            if (collisionFigure(game))
                moveFigureLeft(game->figure);
            break;
        }
        case TET_PLAYER_LEFT:
        {
            moveFigureLeft(game->figure);
            if (collisionFigure(game))
                moveFigureRight(game->figure);
            break;
        }
        case TET_PLAYER_DOWN:
        {
            moveFigureDown(game->figure);
            if (collisionFigure(game))
            {
                moveFigureUp(game->figure);
                placeFigure(game);
                game->score += eraseLines(game);
                updateFigure(game);
            }
            break;
        }
        case TET_PLAYER_NOP:
        default:
            break;
        }
        game->counterIter++;
    }
}

// void calculateTet(TetGame *tetg)
// {
//     if (tetg->ticks_left <= 0)
//     {
//         tetg->ticks_left = tetg->ticks;
//         moveFigureDown(tetg);
//         if (collisionTet(tetg))
//         {
//             moveFigureUp(tetg);
//             plantFigure(tetg);
//             tetg->score += eraseLinesTet(tetg);
//             dropNewFigure(tetg);
//             if (collisionTet(tetg))
//             {
//                 tetg->playing = TET_GAMEOVER;
//                 return;
//             }
//         }
//     }
//     switch (tetg->player->action)
//     {
//     case TET_PLAYER_RIGHT:
//     {
//         moveFigureRight(tetg);
//         if (collisionTet(tetg))
//             moveFigureLeft(tetg);
//         break;
//     }
//     case TET_PLAYER_LEFT:
//     {
//         moveFigureLeft(tetg);
//         if (collisionTet(tetg))
//             moveFigureRight(tetg);
//         break;
//     }
//     case TET_PLAYER_DOWN:
//     {
//         moveFigureDown(tetg);
//         if (collisionTet(tetg))
//             moveFigureUp(tetg);
//         break;
//     }
//     case TET_PLAYER_UP:
//     {
//         TetFigure *t = rotTetFigure(tetg);
//         TetFigure *told = tetg->figure;

//         tetg->figure = t;
//         if (collisionTet(tetg))
//         {
//             tetg->figure = told;
//             freeTetFigure(t);
//         }
//         else
//             freeTetFigure(told);
//         break;
//     }

//     case TET_PLAYER_NOP:
//     default:
//         break;
//     }
//     tetg->ticks_left--;
// }

#endif