#ifndef FRONTEND_C
#define FRONTEND_C

#include "frontend.h"
#include "ncurses.h"
#include "tetris.h"

// Вывести фигуру на поле с учетом смещения по оси X и Y
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

// Инициализирует окна
TetWindows_t *createWindows()
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

// Выводит информацию о игре
void ouputInfoGame(TetGame_t *game)
{
    mvprintw(SHIFT_FIELD_Y + 8, SHIFT_FIELD_X + 33, "%s", "speed:");
    mvprintw(SHIFT_FIELD_Y + 8, SHIFT_FIELD_X + 39, "%d", game->gameInfo->speed);

    mvprintw(SHIFT_FIELD_Y + 9, SHIFT_FIELD_X + 33, "%s", "curr score:");
    mvprintw(SHIFT_FIELD_Y + 9, SHIFT_FIELD_X + 45, "%d", game->gameInfo->score);

    mvprintw(SHIFT_FIELD_Y + 10, SHIFT_FIELD_X + 33, "%s", "high score:");
    mvprintw(SHIFT_FIELD_Y + 10, SHIFT_FIELD_X + 45, "%d", game->gameInfo->high_score);
}

// Вывод всех объектов игры
void frontend(TetGame_t *game, TetWindows_t *winTet)
{
    outputField(game->field, winTet->winField);
    outputFigure(game->figure, winTet->winField);

    cleanSymbols(winTet->winFigure, FIGURE_SIZE, FIGURE_SIZE);
    outputFigure(game->figureNext, winTet->winFigure);
    // ouputInfoGame(game);

    wrefresh(winTet->winFigure);
    wrefresh(winTet->winField);
    wrefresh(winTet->winInfo);
    wrefresh(winTet->winButtons);
}
#endif