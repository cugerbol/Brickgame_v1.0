
#include "tetris.h"
#include "backend.h"
#include "../../gui/frontend.h"
#include "ncurses.h"
#include "fsm.h"
#include "bonus.h"

#include <ncurses.h>

// https://www.opennet.ru/docs/RUS/lpg/node8.html

int main()
{

    TetWindows_t *winTet = tetrisGUI();
    tetrisGame(winTet);

    return 0;
}
