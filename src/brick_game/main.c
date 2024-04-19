
#include "tetris/tetris.h"
#include "tetris/backend.h"
#include "../gui/frontend.h"
#include "ncurses.h"
#include "tetris/fsm.h"
#include "tetris/bonus.h"
#include <ncurses.h>

// Главная функция отвечающая за игру
int tetrisGame(TetWindows_t *winTet);

int main()
{

    TetWindows_t *winTet = tetrisGUI();
    tetrisGame(winTet);

    return 0;
}

int tetrisGame(TetWindows_t *winTet)
{
    TetGame_t *game = initGame();
    while (game->gameStatus != Terminate)
    {
        userAction(game);
        if (game->gameStatus != Pause)
        {
            updateCurrentState(game);
        }
        usleep(2000);
        if (winTet)
            frontend(game, winTet);
    }
    freeGame(game);
    if (winTet)
    {
        freeWindows(winTet);
        endwin();
    }

    return 0;
}