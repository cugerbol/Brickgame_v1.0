#ifndef FRONTEND_C
#define FRONTEND_C

#include "frontend.h"
#include "ncurses.h"
#include "tetris.h"

// Инициализирует окна
TetWindows_t *
createWindows()
{
    TetWindows_t *winTet = (TetWindows_t *)malloc(sizeof(TetWindows_t));
    if (winTet == NULL)
    {
        return NULL;
    }
    int y_field_start = SHIFT_FIELD_Y;
    int x_field_start = SHIFT_FIELD_X;
    int y_field_size = HEIGHT_FIELD + 2;
    int x_field_size = WIDTH_FIELD * 2 + 2;
    winTet->winField = newwin(y_field_size, x_field_size, y_field_start, x_field_start);

    int y_figure_start = y_field_start;
    int x_figure_start = x_field_start + x_field_size;
    int y_figure_size = FIGURE_SIZE + 3;
    int x_figure_size = FIGURE_SIZE * 2 + 4;
    winTet->winFigure = newwin(y_figure_size, x_figure_size, y_figure_start, x_figure_start);

    int y_info_start = y_figure_start + y_figure_size;
    int x_info_start = x_figure_start;
    int y_info_size = y_field_size - y_figure_size;
    int x_info_size = x_figure_size;
    winTet->winInfo = newwin(y_info_size, x_info_size, y_info_start, x_info_start);

    int y_buttons_start = y_field_start + y_field_size;
    int x_buttons_start = x_field_start;
    int y_buttons_size = 5;
    int x_buttons_size = x_field_size + x_figure_size;
    winTet->winButtons = newwin(y_buttons_size, x_buttons_size, y_buttons_start, x_buttons_start);

    refresh();

    box(winTet->winField, 0, 0);
    box(winTet->winFigure, 0, 0);
    box(winTet->winInfo, 0, 0);
    box(winTet->winButtons, 0, 0);
    return winTet;
}

// Освободить память окон
void freeWindows(TetWindows_t *winTet)
{
    if (winTet)
        free(winTet);
}

// Вывести фигуру на поле
void outputFigure(TetFigure_t *figure, WINDOW *win)
{
    for (int row = 0; row < FIGURE_SIZE; row++)
    {
        for (int col = 0; col < FIGURE_SIZE; col++)
        {

            int fy = figure->y + row;
            int fx = figure->x + col;

            if (figure->blocks[row][col] != 0 && fy >= 0)
            {
                wbkgdset(win, COLOR_PAIR(figure->color));
                mvwprintw(win, fy + 1, 2 * fx + 1, "%c", ' ');
                mvwprintw(win, fy + 1, 2 * fx + 2, "%c", ' ');
            }
        }
    }
}

// Вывести на экран поле
void outputField(TetField_t *field, WINDOW *win)
{
    for (int row = 0; row < HEIGHT_FIELD; row++)
    {
        for (int col = 0; col < WIDTH_FIELD; col++)
        {
            {
                if (field->blocks[row][col] == 0)
                {

                    wbkgdset(win, COLOR_PAIR(WHITE));
                    mvwprintw(win, row + 1, 2 * col + 1, "%c", ' ');
                    mvwprintw(win, row + 1, 2 * col + 2, "%c", ' ');
                }
                else
                {
                    wbkgdset(win, COLOR_PAIR(GREEN));
                    mvwprintw(win, row + 1, 2 * col + 1, "%c", ' ');
                    mvwprintw(win, row + 1, 2 * col + 2, "%c", ' ');
                }
            }
        }
    }
}

// Очистить все символы в координатах
void cleanSymbols(WINDOW *win, int size_y, int size_x)
{
    for (int row = 0; row <= size_y; row++)
    {
        for (int col = 0; col <= size_x; col++)
        {
            wbkgdset(win, COLOR_PAIR(WHITE));
            mvwprintw(win, row + 1, 2 * col + 2, "%c", ' ');
            mvwprintw(win, row + 1, 2 * col + 1, "%c", ' ');
        }
    }
}

// Выводит информацию о игре
void ouputInfoGame(TetGame_t *game, WINDOW *win)
{
    mvwprintw(win, 2, 2, "%s", "speed:");
    mvwprintw(win, 2, 10, "%d ", game->gameInfo->speed);

    mvwprintw(win, 3, 2, "%s", "level:");
    mvwprintw(win, 3, 10, "%d ", game->gameInfo->level);

    mvwprintw(win, 4, 2, "%s", "score:");
    mvwprintw(win, 5, 2, "%d  ", game->gameInfo->score);

    mvwprintw(win, 6, 2, "%s", "record:");
    mvwprintw(win, 7, 2, "%d ", game->gameInfo->record);
}

// Выводит окно кнопок
void outputButtons(WINDOW *win)
{
    mvwprintw(win, 1, 3, "%s", "Quit(Q)");
    mvwprintw(win, 3, 3, "%s", "Pause(P)");

    mvwprintw(win, 1, 20, "%s", "Speed up(+)");
    mvwprintw(win, 3, 20, "%s", "Speed down(-)");
}

// Выводит GameOver
void outpuGameOver(WINDOW *win, TetGame_t *game)
{
    wbkgdset(win, COLOR_PAIR(3));
    for (int i = 4; i < 7; i++)
    {
        for (int j = 5; j < 18; j++)
        {

            mvwprintw(win, i, j, "%c", ' ');
        }
    }
    mvwprintw(win, 5, 7, "%s", "GAME OVER");
    wrefresh(win);
}

// Вывод всех объектов игры
void frontend(TetGame_t *game, TetWindows_t *winTet)
{

    if (game->gameStatus == Start)
    {
        outputField(game->field, winTet->winField);
        outputFigure(game->figure, winTet->winField);

        cleanSymbols(winTet->winFigure, FIGURE_SIZE, FIGURE_SIZE);
        outputFigure(game->figureNext, winTet->winFigure);
        ouputInfoGame(game, winTet->winInfo);
        outputButtons(winTet->winButtons);
    }

    if (game->gameStatus == GameOver)
    {
        outpuGameOver(winTet->winField, game);
    }

    wrefresh(winTet->winFigure);
    wrefresh(winTet->winField);
    wrefresh(winTet->winInfo);
    wrefresh(winTet->winButtons);
}
#endif