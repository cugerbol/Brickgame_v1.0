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
    game->gameInfo = (GameInfo_t *)malloc(sizeof(GameInfo_t));

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
    int rn = rand() % 7 + 1;
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

// Поворот фигуры
void rotateFigure(TetFigure_t *figure)
{
    TetFigure_t *figureTmp = createFigure();
    for (int row = 0; row < FIGURE_SIZE; row++)
    {
        for (int col = 0; col < FIGURE_SIZE; col++)
        {
            figureTmp->blocks[col][row] = figure->blocks[row][FIGURE_SIZE - col - 1];
        }
    }
    for (int row = 0; row < FIGURE_SIZE; row++)
    {
        free(figure->blocks[row]);
    }
    figure->blocks = figureTmp->blocks;
    free(figureTmp);
}

// Выкинуть новую фигуру
void updateFigure(TetGame_t *game)
{
    freeFigure(game->figure);
    game->figure = game->figureNext;
    game->figure->y = -5;
    game->figureNext = createRandomFigure();
}

// Проверяет находится ли блок в пределах игрового поля
int checkBoundaries(int row, int col, int fy, int fx)
{
    int result = 1;
    if ((row + fy > HEIGHT_FIELD - 1 || row + fy < 0) ||
        (col + fx > WIDTH_FIELD - 1 || col + fx < 0))
        result = 0;
    return result;
}

// Установить фигуру на поле
void placeFigure(TetGame_t *game)
{
    int fy = game->figure->y;
    int fx = game->figure->x;

    for (int row = 0; row < FIGURE_SIZE; row++)
    {
        for (int col = 0; col < FIGURE_SIZE; col++)
        {
            int fgr = game->figure->blocks[row][col];
            if (fgr != 0 && fy + row >= 0)
            {
                game->field->blocks[fy + row][fx + col] = fgr;
            }
        }
    }
}

// Проверяет заполнена ли линия под индексом row
int lineIsFill(TetField_t *field, int row)
{
    int result = 1;
    for (int col = 0; col < WIDTH_FIELD; col++)
    {
        int block = field->blocks[row][col];
        if (block == 0)
            result = 0;
    }
    return result;
}

// Удаляет строку
void dropLine(TetField_t *field, int row)
{
    if (row == HEIGHT_FIELD)
    {
        for (int col = 0; col < WIDTH_FIELD; col++)
            field->blocks[row][col] = 0;
    }
    else
    {
        for (int i = row; i > 0; i--)
        {
            for (int col = 0; col < WIDTH_FIELD; col++)
            {
                field->blocks[i][col] = field->blocks[i - 1][col];
            }
        }
    }
}

// Удаляет строки и подсчитывает результат
int eraseLines(TetGame_t *game)
{
    int counter = 0;
    for (int row = HEIGHT_FIELD - 1; row >= 0; row--)
    {
        while (lineIsFill(game->field, row))
        {
            dropLine(game->field, row);
            counter++;
        }
    }
    return counter;
}

// Проверка столкновения фигуры
int collisionFigure(TetGame_t *game)
{
    int result = 0;

    int fx = game->figure->x;
    int fy = game->figure->y;

    int **figure = game->figure->blocks;
    int **field = game->field->blocks;

    for (int row = 0; row < FIGURE_SIZE; row++)
    {
        for (int col = 0; col < FIGURE_SIZE; col++)
        {
            int fgr = figure[row][col];

            if (fgr == 1)
            {
                if (fy + row < 0)
                    continue;

                else if (checkBoundaries(row, col, fy, fx))
                {
                    int fld = field[fy + row][fx + col];

                    if (fgr != 0 && fld != 0)
                    {
                        result = 1;

                        if (fy + row == 0)
                            game->gameStatus = Terminate;

                        break;
                    }
                }

                else if (!checkBoundaries(row, col, fy, fx))
                {
                    result = 1;
                    break;
                }
            }
        }
        if (result)
            break;
    }
    return result;
}
#endif
