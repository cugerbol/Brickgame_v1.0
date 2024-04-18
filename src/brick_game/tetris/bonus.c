#ifndef BONUS_C
#define BONUS_C

#include "tetris.h"
#include "bonus.h"

// int main()
// {
//     printf("%d\n", readDataBase());
//     writeDataBase(250);
//     printf("%d\n", readDataBase());

//     return 0;
// }

// Увеличение уровня в зависимости от score
void levelUp(TetGame_t *game)
{
    int sc = game->gameInfo->score;
    game->gameInfo->level = 1 + sc / 600;

    while (game->gameInfo->speed < game->gameInfo->level)
    {
        game->gameInfo->speed++;
    }
}

// Переводит кол-во уничтоженных уровней (строк) в score
int converterScore(int count_rows)
{
    int result = 0;
    if (count_rows == 1)
        result = 100;

    else if (count_rows == 2)
        result = 300;

    else if (count_rows == 3)
        result = 700;

    else if (count_rows >= 4)
        result = 1500;

    return result;
}

// Читает из базы данных максимальный score
int readDataBase()
{
    int score = 0;
    char fileName[] = "./database/database.txt";
    FILE *file = fopen(fileName, "r");
    if (file)
    {
        int ch;
        while ((ch = fgetc(file)) != EOF)
        {
            if (ch >= '0' && ch <= '9')
            {
                score = score * 10 + (ch - '0');
            }
            else
            {
                break;
            }
        }
    }

    fclose(file);
    return score;
}

// Записывает в базу данных максимальный score
int writeDataBase(int score)
{
    char fileName[] = "./database/database.txt";
    FILE *file = fopen(fileName, "w");
    if (file)
    {
        // Используем fprintf для записи целого числа в файл
        fprintf(file, "%d", score);
    }

    fclose(file);
    return 0;
}

#endif