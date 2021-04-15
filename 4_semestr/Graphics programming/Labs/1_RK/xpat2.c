#include "xchess.h"

static cell **box;

//Получение ссылки на одноименный массив структур из дисплейного модуля
int relink(cell **boxing)
{
    box = boxing;
    return 0;
}

//Функция атаки одиночной фигуры
int attack(int start_x, int start_y, int end_x, int end_y)
{
    if ((end_x - start_x == 0) || (end_y - start_y == 0) || (end_x - start_x == end_y - start_y) || (end_x - start_x == start_y - end_y))
        return 0;
    return 1;
}

//Установка полей атаки для отдельной фигуры
int set_attack(int y, int x)
{
    int ny, nx;
    for (ny = y, nx = x+1; nx < COLS; nx++)
        box[ny][nx].type = UNDERRATACK;
    for (ny = y+1, nx = x; ny < 8; ny++)
        box[ny][nx].type = UNDERRATACK;
    for (ny = y, nx = x-1; nx >= 0; nx--)
        box[ny][nx].type = UNDERRATACK;
    for (ny = y-1, nx = x; ny >= 0; ny--)
        box[ny][nx].type = UNDERRATACK;


    for (ny = y+1, nx = x+1; (nx < 8) && (ny < 8); nx++, ny++)
        box[ny][nx].type = UNDERRATACK;
    for (ny = y+1, nx = x-1; (nx >= 0) && (ny < 8); nx--, ny++)
        box[ny][nx].type = UNDERRATACK;
    for (ny = y-1, nx = x+1; (nx < 8) && (ny >= 0); nx++, ny--)
        box[ny][nx].type = UNDERRATACK;
    for (ny = y-1, nx = x-1; (nx >= 0) && (ny >= 0); nx--, ny--)
        box[ny][nx].type = UNDERRATACK;
    return 0;
}

//Перерисовка полей атаки фигур
int reattack()
{
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            box[i][j].type = NOTUNDERRATACK;

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (box[i][j].figure == 1)
                set_attack(i,j);

    return 0;
}

//Проверка правил изменения позиции фигуры
int CheckRules(int start_x, int start_y, int end_x, int end_y)
{
    if (box[end_y][end_x].figure == 1)
        return 0;
    if (attack(start_x, start_y, end_x, end_y) == 0) {
        box[end_y][end_x].figure = 1;
        box[start_y][start_x].figure = 0;
        reattack();
    }
    return 0;
}

//Задание начального расположения фигур
int desk_setter()
{
    static short position[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 1, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 1, 0, 0, 0},
                                   {0, 0, 0, 1, 0, 0, 0, 0},
                                   {0, 0, 1, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0},
                                   {1, 0, 0, 0, 0, 0, 0, 0}};

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            box[i][j].figure = position[i][j];

    reattack();
    return 0;
}

