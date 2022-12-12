/*
** EPITECH PROJECT, 2022
** B-PSU-100-RUN-1-1-sokoban-pierre-alexandre.grosset
** File description:
** loops
*/

#include "sokoban_header.h"

const int list[] = {0, 1, 2, 3, 4};
const int move_x[] = {0, 0, 0, 1, -1};
const int move_y[] = {0, -1, 1, 0, 0};

void check_win (storage_t **storage)
{
    int i = 0;
    int check = 0;
    chtype cht;
    char chr;
    while (storage[i] != NULL) {
        cht = mvinch(storage[i]->y, storage[i]->x);
        chr = cht & A_CHARTEXT;
        if (chr == 'X')
            check++;
        i++;
    }
    if (check == i) {
        refresh();
        usleep(1000000);
        endwin();
        exit(0);
    }
}

void loop(char const *buffer, player_t player, storage_t **storage)
{
    int move = 0;
    int i;
    while (true) {;
        move = event_handler(getch());
        if (move == 0)
            process(buffer);
        for (i = 0; move != list[i] && is_token('0' + move, VALID_MOVE); i++);
        moves(&player, move_x[i], move_y[i]);
        check_win(storage);
        check_o(storage);
    }
}

int process(char const *buffer)
{
    player_t player = init_player(buffer);
    WINDOW *window = initscr();
    storage_t **storage = add_storage(buffer);
    clear();
    mvprintw(0, 0, "%s" , buffer);
    keypad(window, true);
    curs_set(0);
    noecho();
    loop(buffer, player, storage);
    endwin();
    return 0;
}
