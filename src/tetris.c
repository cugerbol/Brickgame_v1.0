
#include "tetris.h"
#include "backend.h"
#include "frontend.h"
#include "ncurses.h"
#include "fsm.h"

#include <ncurses.h>

void userAction(TetGame_t *game);

int main()
{
    initscr();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    raw();
    noecho();
    cbreak();
    curs_set(0);

    start_color();

    init_pair(4, COLOR_WHITE, COLOR_WHITE);
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    init_pair(3, COLOR_CYAN, COLOR_BLUE);

    // init_pair(1, COLOR_YELLOW, COLOR_GREEN);
    // init_pair(2, COLOR_CYAN, COLOR_BLUE);
    // init_pair(3, COLOR_BLACK, COLOR_WHITE);
    // init_pair(4, COLOR_RED, COLOR_MAGENTA);

    TetGame_t *game = createGame();
    initGame(game);

    while (1) //(game->gameStatus != 100)
    {
        userAction(game);

        if (game->gameStatus != Pause)
        {
            updateCurrentState(game);
            frontend(game);
        }
        usleep(2000);

        if (game->gameStatus == Terminate)
        {
            usleep(2000000); // Временно
            break;
        }
    }
    endwin();
    return 0;
}

void userAction(TetGame_t *game)
{
    int ch = getch();
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
        else
            game->gameStatus = Pause;
        break;
    default:
        game->action = Action;
        break;
    }
}
