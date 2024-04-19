#ifndef FSM_C
#define FSM_C

#include "tetris.h"
#include "backend.h"
#include "fsm.h"
#include "bonus.h"
#include "ncurses.h"

// Функция для просчета одной итерации
void calculateTet(TetGame_t *game)
{
    if (game->counterIter >= COUNT_ITERATION * 15 / game->gameInfo->speed)
    {
        game->counterIter = 0;
        moveFigureDown(game->figure);

        if (collisionFigure(game))
        {
            moveFigureUp(game->figure);
            placeFigure(game);
            int count_rows = eraseLines(game);
            game->gameInfo->score = game->gameInfo->score + converterScore(count_rows);
            levelUp(game);
            updateFigure(game);
            if (collisionFigure(game))
            {
                game->gameStatus = GameOver;
            }
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
                int count_rows = eraseLines(game);
                game->gameInfo->score = game->gameInfo->score + converterScore(count_rows);
                levelUp(game);
                updateFigure(game);
                if (collisionFigure(game))
                {
                    game->gameStatus = GameOver;
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

// Изменение состояний игры в зависимости от действий игрока
void userAction(TetGame_t *game, int ch)
{

    switch (ch)
    {
    case KEY_UP:
        game->action = Up;
        break;
    case KEY_DOWN:
        game->action = Down;
        break;
    case KEY_LEFT:
        game->action = Left;
        break;
    case KEY_RIGHT:
        game->action = Right;
        break;
    case 'q':
        game->gameStatus = Terminate;
        break;
    case 'p':
        if (game->gameStatus == Pause)
            game->gameStatus = Start;
        else if ((game->gameStatus != GameOver))
            game->gameStatus = Pause;
        break;
    case '+':
    case '=':
        if (game->gameInfo->speed > 0 && game->gameInfo->speed < 10)
            game->gameInfo->speed++;
        break;
    case '_':
    case '-':
        if (game->gameInfo->speed > 1 && game->gameInfo->speed <= 10 && game->gameInfo->speed > game->gameInfo->level)
            game->gameInfo->speed--;
        break;

    default:
        game->action = Action;
        break;
    }
}

// Обновляет текущий состояние игры
TetGame_t *updateCurrentState(TetGame_t *game)
{
    calculateTet(game);
    if (game->gameInfo->score > game->gameInfo->record)
    {
        game->gameInfo->record = game->gameInfo->score;
        writeDataBase(game->gameInfo->record);
    }
    return game;
}
#endif

// Инициализировать новую игру
TetGame_t *initGame()
{
    srand((unsigned)time(NULL));

    TetGame_t *game = createGame();

    game->figure = createRandomFigure(0);
    game->figure->x = FIGURE_START_X;

    game->figureNext = createRandomFigure(0);
    game->field = createField();

    game->action = Start;

    game->gameInfo->level = 1;
    game->gameInfo->record = readDataBase();

    game->gameInfo->score = 0;
    game->gameInfo->speed = START_SPEED;

    game->counterIter = 1;

    return game;
}
