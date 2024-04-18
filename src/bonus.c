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
    int d = 1;
    char fileName[] = "./database/database.txt";
    FILE *file = fopen(fileName, "r");
    if (file)
    {
        char ch;
        int elem = 0;
        while ((ch = fgetc(file)) != EOF)
        {

            int s = (int)(ch - '0') * d;
            d = d * 10;
            score = score + s;
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
        fputc(score, file);
    }

    fclose(file);
    return 0;
}

#endif