/*
** EPITECH PROJECT, 2022
** bonus-sokoban
** File description:
** inits
*/

#include "sokoban_bonus.h"

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

int menu(void)
{
    int key = 0;
    int answer = 1;
    mvprintw(LINES / 2, COLS / 2, "PLAY");
    mvprintw(LINES / 2 + 1, COLS / 2, "EXIT");
    mvprintw(LINES / 2, COLS / 2 - 1, ">");
    while (key != '\n') {
        key = getch();
        if (key == KEY_UP) {
            answer = 1;
            mvprintw(LINES / 2, COLS / 2 - 1, ">");
            mvprintw(LINES / 2 + 1, COLS / 2 - 1, " ");
        }
        if (key == KEY_DOWN) {
            answer = -1;
            mvprintw(LINES / 2 + 1, COLS / 2 - 1, ">");
            mvprintw(LINES / 2, COLS / 2 - 1, " ");
        }
    }
    return answer;
}

void game_init(game_t *game)
{
    game->player1 = init_player(game->buffer, 'P');
    game->player2 = init_player(game->buffer, 'L');
    game->window = initscr();
    keypad(game->window, true);
    game->storage = add_storage(game->buffer);
    curs_set(0);
    noecho();
    if (menu() == -1)
        end_game(game);
    clear();
    mvprintw(0, 0, "%s" , game->buffer);
}

player_t init_player(char const *buffer, char player_fd)
{
    player_t player = {0, 0};
    int i = 0;
    while (buffer[i] != player_fd) {
        player.pos_x++;
        if (buffer[i] == '\n') {
            player.pos_x = 0;
            player.pos_y++;
        }
        i++;
    }
    return player;
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
