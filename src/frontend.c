#ifndef FRONTEND_C
#define FRONTEND_C

#include "frontend.h"
#include "ncurses.h"
#include "tetris.h"

// Вывести фигуру на поле с учетом смещения по оси X и Y
void outputFigure(TetFigure_t *figure, char symb, int shift_y, int shift_x)
{
    for (int row = 0; row < FIGURE_SIZE; row++)
    {
        for (int col = 0; col < FIGURE_SIZE; col++)
        {
            int fy = figure->y + row + SHIFT_FIELD_Y + shift_y;
            int fx = figure->x + col + SHIFT_FIELD_X + shift_x;

            if (figure->blocks[row][col] != 0)
                mvprintw(fy, fx, "%c", symb);
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
            mvprintw(row + SHIFT_FIELD_Y, col + SHIFT_FIELD_X, "%d", field->blocks[row][col]);
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
                     col + x + SHIFT_FIELD_X, "%c", ' ');
        }
    }
}

// Выводит информацию о игре
void ouputInfoGame(TetGame_t *game)
{
    mvprintw(SHIFT_FIELD_Y + 7, SHIFT_FIELD_X + 12, "%s", "speed:");
    mvprintw(SHIFT_FIELD_Y + 7, SHIFT_FIELD_X + 20, "%d", game->gameInfo->speed);

    mvprintw(SHIFT_FIELD_Y + 9, SHIFT_FIELD_X + 12, "%s", "curr score:");
    mvprintw(SHIFT_FIELD_Y + 9, SHIFT_FIELD_X + 25, "%d", game->gameInfo->score);

    mvprintw(SHIFT_FIELD_Y + 10, SHIFT_FIELD_X + 12, "%s", "high score:");
    mvprintw(SHIFT_FIELD_Y + 10, SHIFT_FIELD_X + 25, "%d", game->gameInfo->high_score);
}

// Вывод всех объектов игры
void frontend(TetGame_t *game)
{

    // box(stdscr, 2, 2);
    outputField(game->field);
    outputFigure(game->figure, '2', 0, 0);

    cleanSymbols(2, 12, 5, 5);
    outputFigure(game->figureNext, '2', 2, 12);
    ouputInfoGame(game);
    refresh();
}
#endif