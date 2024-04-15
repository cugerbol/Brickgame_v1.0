

#include "tetris.h"
#include "backend.h"
#include "frontend.h"
#include "ncurses.h"
#include "fsm.h"

int main()
{

    initscr();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();
    cbreak();
    curs_set(0);

    TetGame_t *game = createGame();
    char ch = 'a';

    while (game->action != 'q')
    {
        game->action = getch();
        calculateTet(game);
        frontend(game);

        usleep(10000);
    }
    endwin();
    return 0;
}