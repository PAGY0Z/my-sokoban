/*
** EPITECH PROJECT, 2022
** B-PSU-100-RUN-1-1-sokoban-pierre-alexandre.grosset
** File description:
** init_plyaer
*/

#include "sokoban_header.h"

player_t init_player(char const *buffer)
{
    player_t player = {0, 0};
    int i = 0;
    while (buffer[i] != 'P') {
        player.pos_x++;
        if (buffer[i] == '\n') {
            player.pos_x = 0;
            player.pos_y++;
        }
        i++;
    }
    return player;
}

int count_holes(char const *buffer)
{
    int i = 0;
    int O_count = 0;
    while (buffer[i] != '\0') {
        if (buffer[i] == 'O')
            O_count++;
        i++;
    }
    return O_count;
}

storage_t **add_storage(char const *buffer)
{
    int count = count_holes(buffer);
    int i = 0;
    int x = 0;
    int y = 0;
    storage_t **storage = malloc(sizeof(storage_t*) * count + 1);
    for (int j = 0; buffer[j] != '\0'; j++, x++) {
        if (buffer[j] == 'O') {
            storage[i] = malloc(sizeof(storage_t));
            storage[i]->x = x - 1;
            storage[i++]->y = y;
        }
        if (buffer[j] == '\n') {
            y++;
            x = 0;
        }
    }
    storage[i] = NULL;
    return storage;
}
