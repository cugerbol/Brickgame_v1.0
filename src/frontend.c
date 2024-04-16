#ifndef FRONTEND_C
#define FRONTEND_C

#include "frontend.h"
#include "ncurses.h"
#include "tetris.h"

// Вывести фигуру на поле с учетом смещения по оси X и Y
void outputFigure(TetFigure_t *figure, char symb, int color, int shift_y, int shift_x)
{
    for (int row = 0; row < FIGURE_SIZE; row++)
    {
        for (int col = 0; col < FIGURE_SIZE; col++)
        {
            int fy = figure->y + row + SHIFT_FIELD_Y + shift_y;
            int fx = figure->x + col + SHIFT_FIELD_X + shift_x;

            // for (int i = 1; i <= 2; i++)
            // {
            if (figure->blocks[row][col] != 0)
            {
                attron(COLOR_PAIR(color));
                mvprintw(fy, 2 * fx, "%c", symb);
                mvprintw(fy, 2 * fx + 1, "%c", symb);
                attroff(COLOR_PAIR(color));
            }
        }
    }
}

// Вывести на экран поле
void outputField(TetField_t *field)
{
    for (int row = 0; row < HEIGHT_FIELD; row++)
    {
        for (int col = 0; col < WIDTH_FIELD; col++)
        {
            {
                if (field->blocks[row][col] == 0)
                {
                    attron(COLOR_PAIR(4));
                    mvprintw(row + SHIFT_FIELD_Y, 2 * (col + SHIFT_FIELD_X), "%c", ' ');
                    mvprintw(row + SHIFT_FIELD_Y, 2 * (col + SHIFT_FIELD_X) + 1, "%c", ' ');
                    attroff(COLOR_PAIR(4));
                }
                else
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(row + SHIFT_FIELD_Y, 2 * (col + SHIFT_FIELD_X), "%c", ' ');
                    mvprintw(row + SHIFT_FIELD_Y, 2 * (col + SHIFT_FIELD_X) + 1, "%c", ' ');
                    attroff(COLOR_PAIR(3));
                }
            }
        }
    }
}

// Очистить все символы в координатах
void cleanSymbols(int y, int x, int size_y, int size_x)
{
    for (int row = 0; row < size_y; row++)
    {
        for (int col = 0; col <= size_y; col++)
        {
            mvprintw(row + y + SHIFT_FIELD_Y,
                     2 * (col + x + SHIFT_FIELD_X), "%c", ' ');
            mvprintw(row + y + SHIFT_FIELD_Y,
                     2 * (col + x + SHIFT_FIELD_X) + 1, "%c", ' ');
        }
    }
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
void frontend(TetGame_t *game)
{
    outputField(game->field);
    outputFigure(game->figure, ' ', 1, 0, 0);

    cleanSymbols(2, 12, 5, 5);
    outputFigure(game->figureNext, ' ', 2, 2, 12);
    ouputInfoGame(game);
    refresh();
}
#endif