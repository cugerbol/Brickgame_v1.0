#ifndef BACKEND_C
#define BACKEND_C

#include "tetris.h"
#include "backend.h"

// Создать фигуру заполненную нулями
TetFigure_t *createFigure()
{
    TetFigure_t *figure = (TetFigure_t *)malloc(sizeof(TetFigure_t));
    figure->blocks = (int **)calloc(FIGURE_SIZE, sizeof(int *));
    for (int row = 0; row < FIGURE_SIZE; row++)
    {
        figure->blocks[row] = (int *)calloc(FIGURE_SIZE, sizeof(int));
    }

    figure->y = 0;

    return figure;
}

// Освободить выделенную для фигуры память
void freeFigure(TetFigure_t *figure)
{
    if (figure)
    {
        if (figure->blocks)
        {
            for (int row = 0; row < FIGURE_SIZE; row++)
            {
                free(figure->blocks[row]);
            }
            free(figure);
        }
    }
}

// Создать поле размером HEIGHT_FIELD на WIGHT_FIELD заполненное нулями
TetField_t *createField()
{
    TetField_t *field = (TetField_t *)malloc(sizeof(TetField_t));
    field->blocks = (int **)calloc(HEIGHT_FIELD, sizeof(int *));
    for (int row = 0; row < HEIGHT_FIELD; row++)
    {
        field->blocks[row] = (int *)calloc(WIDTH_FIELD, sizeof(int));
    }
    return field;
}

// Освободить выделенную для поля память
void freeField(TetField_t *field)
{
    if (field)
    {
        if (field->blocks)
        {
            for (int row = 0; row < FIGURE_SIZE; row++)
            {
                free(field->blocks[row]);
            }
            free(field);
        }
    }
}

// Создать игру
TetGame_t *createGame()
{
    TetGame_t *game = (TetGame_t *)malloc(sizeof(TetGame_t));
    game->figure = createRandomFigure();
    game->figureNext = createRandomFigure();
    game->field = createField();
    game->action = 'w';
    game->counterIter = 1;

    return game;
}

// Освободить выделенную для игры память
void freeGame(TetGame_t *game)
{
    if (game)
    {
        freeFigure(game->figure);
        freeFigure(game->figureNext);
        freeField(game->field);
        free(game);
    }
}

// Создать фигуру из паттернов
TetFigure_t *createRandomFigure()
{
    TetFigure_t *figure = createFigure();
    int rn = rand() % 2 + 1;
    char fileName[20];
    sprintf(fileName, "./templates/%d.txt", rn);
    FILE *file = fopen(fileName, "r");
    if (file)
    {
        char ch;
        int elem = 0;
        while ((ch = fgetc(file)) != EOF)
        {
            int number = ch - '0';
            if (number == 1 || number == 0)
            {
                figure->blocks[elem / 5][elem % 5] = number;
                elem++;
            }
        }
    }
    fclose(file);
    return figure;
}

// Движение фигуры по Y вниз
void moveFigureDown(TetFigure_t *figure)
{
    figure->y++;
}

// Движение фигуры по Y вверх
void moveFigureUp(TetFigure_t *figure)
{
    figure->y--;
}

// Движение фигуры по X влево
void moveFigureLeft(TetFigure_t *figure)
{
    figure->x--;
}

// Движение фигуры по X вправо
void moveFigureRight(TetFigure_t *figure)
{
    figure->x++;
}

// Выкинуть новую фигуру
void updateFigure(TetGame_t *game)
{
    freeFigure(game->figure);
    game->figure = game->figureNext;
    game->figureNext = createRandomFigure();
}

#endif
