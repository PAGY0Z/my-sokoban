/*
** EPITECH PROJECT, 2022
** B-PSU-100-RUN-1-1-bssokoban-pierre-alexandre.grosset
** File description:
** main
*/

#include "sokoban_header.h"

int event_handler(int key)
{
    if (key == ' ')
        return 0;
    if (key == KEY_UP)
        return 1;
    if (key == KEY_DOWN)
        return 2;
    if (key == KEY_RIGHT)
        return 3;
    if (key == KEY_LEFT)
        return 4;
    return -1;
}

void moves(player_t *player, int x, int y)
{
    chtype n1_cht = mvinch(player->pos_y + y, player->pos_x + x);
    char n1_char = n1_cht & A_CHARTEXT;
    chtype n2_cht = mvinch(player->pos_y + (2 * y), player->pos_x + (2 * x));
    char n2_char = n2_cht & A_CHARTEXT;
    if (n1_char == '#')
        return;
    if (n1_char == 'X') {
        if (n2_char == '#' || n2_char == 'X')
            return;
        mvaddch(player->pos_y + (2 * y), player->pos_x + (2 * x), 'X');
    }
    mvaddch(player->pos_y, player->pos_x, ' ');
    player->pos_x += x;
    player->pos_y += y;
    mvaddch(player->pos_y, player->pos_x, 'P');
}

void check_o(storage_t **storage)
{
    int i = 0;
    while (storage[i] != NULL) {
        if ((mvinch(storage[i]->y, storage[i]->x) & A_CHARTEXT) == ' ')
            mvaddch(storage[i]->y, storage[i]->x, 'O');
        i++;
    }
}
