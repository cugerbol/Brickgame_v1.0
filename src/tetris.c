
#include "tetris.h"
#include "backend.h"
#include "frontend.h"
#include "ncurses.h"
#include "fsm.h"

void userInput(UserAction_t action, bool hold);

int main()
{
    initscr();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();
    cbreak();
    curs_set(0);

    TetGame_t *game = createGame();
    initGame(game);

    char ch = 'a';
    while (game->action != 'q')
    {

        game->action = getch();
        updateCurrentState(game);
        frontend(game);
        usleep(2000);

        if (game->gameStatus == Terminate)
            break;
    }
    endwin();
    return 0;
}

// // KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT

// void userInput(UserAction_t action, bool hold)
// {
//     char ch = getch();
//     switch (ch)
//     {
//     case KEY_DOWN:
//         break;

//     case KEY_UP:
//         break;

//     case KEY_LEFT:
//         break;

//     case KEY_RIGHT:
//         break;

//     default:
//         break;
//     }
// }
