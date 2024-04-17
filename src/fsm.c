#ifndef FSM_C
#define FSM_C

#include "tetris.h"
#include "backend.h"
#include "fsm.h"
#include "ncurses.h"

// Функция для просчета одной итерации
void calculateTet(TetGame_t *game)
{
    if (game->counterIter == COUNT_ITERATION * 20 / game->gameInfo->speed)
    {
        game->counterIter = 0;
        moveFigureDown(game->figure);

        if (collisionFigure(game))
        {
            moveFigureUp(game->figure);
            placeFigure(game);
            game->gameInfo->score += eraseLines(game);
            updateFigure(game);
        }
    }
    else
    {
        switch (game->action)
        {
        case Right:
        {
            moveFigureRight(game->figure);
            if (collisionFigure(game))
                moveFigureLeft(game->figure);
            break;
        }
        case Left:
        {
            moveFigureLeft(game->figure);
            if (collisionFigure(game))
                moveFigureRight(game->figure);
            break;
        }
        case Up:
        {
            rotateFigure(game->figure);
            if (collisionFigure(game))
                for (int i = 0; i < 3; i++)
                {
                    rotateFigure(game->figure);
                }
            break;
        }
        case Down:
        {
            moveFigureDown(game->figure);
            if (collisionFigure(game))
            {
                moveFigureUp(game->figure);
                placeFigure(game);
                game->gameInfo->score += eraseLines(game);
                updateFigure(game);
                if (collisionFigure(game))
                {
                    game->gameStatus = Terminate;
                }
            }
            break;
        }
        case Action:
        default:
            break;
        }
        game->counterIter++;
    }
}

// Обновляет текущий состояние игры
TetGame_t *updateCurrentState(TetGame_t *game)
{
    calculateTet(game);
    return game;
}
#endif

// Инициализировать новую игру
void initGame(TetGame_t *game)
{
    game->figure = createRandomFigure();
    game->figureNext = createRandomFigure();
    game->field = createField();

    game->action = Start;

    game->gameInfo->level = 1;
    game->gameInfo->record = 0;

    game->gameInfo->score = 0;
    game->gameInfo->speed = 5;

    game->counterIter = 1;
}

// void userAction(TetGame_t *game)
// {
//     char action = getch();
//     switch ((unsigned int)action)
//     {
//     case (unsigned int)KEY_RIGHT:
//         game->action = Right;
//         break;
//     case (unsigned int)KEY_LEFT:
//         game->action = Left;
//         break;
//     case (unsigned int)KEY_UP:
//         game->action = Up;
//         break;
//     case (unsigned int)KEY_DOWN:
//         game->action = Down;
//         break;
//     case (unsigned int)KEY_ENTER:
//         game->action = Terminate;
//         break;
//     default:
//         game->action = Action;
//         break;
//     }
// }
//  Start,
//     Pause,
//     Terminate,
//     Left,
//     Right,
//     Up,
//     Down,
//     Action