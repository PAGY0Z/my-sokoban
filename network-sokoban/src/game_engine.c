/*
** EPITECH PROJECT, 2022
** bonus-sokoban
** File description:
** game_engine
*/

#include "sokoban_bonus.h"

void check_o(storage_t **storage)
{
    int i = 0;
    while (storage[i] != NULL) {
        if ((mvinch(storage[i]->y, storage[i]->x) & A_CHARTEXT) == ' ')
            mvaddch(storage[i]->y, storage[i]->x, 'O');
        if ((mvinch(storage[i]->y, storage[i]->x) & A_CHARTEXT) == 'X')
            mvaddch(storage[i]->y, storage[i]->x, 'V');
        i++;
    }
}

void check_player(game_t *game)
{
    if ((mvinch(game->player1.pos_y, game->player1.pos_x) & A_CHARTEXT) == ' ')
        mvaddch(game->player1.pos_y, game->player1.pos_x, 'P');
    if ((mvinch(game->player2.pos_y, game->player2.pos_x) & A_CHARTEXT) == ' ')
        mvaddch(game->player2.pos_y, game->player2.pos_x, 'L');
}

void check_win(game_t *game, storage_t **storage)
{
    for (int i = 0; storage[i] != NULL; i++) {
        if ((mvinch(storage[i]->y, storage[i]->x) & A_CHARTEXT) == 'X')
            continue;
        return;
    }
    refresh();
    usleep(1000000);
    end_game(game);
}

int moves(int x, int y, game_t *game, char type)
{
    if (type == 'P') {
        char n1_cht = (mvinch(game->player1.pos_y + y, game->player1.pos_x + x) & A_CHARTEXT);
        char n2_cht = (mvinch(game->player1.pos_y + (2 * y), game->player1.pos_x + (2 * x)) & A_CHARTEXT);
        if (n1_cht == '#')
            return 0;
        if (n1_cht == 'X' || n1_cht == 'V') {
            if (n2_cht == '#' || n2_cht == 'X' || n2_cht == 'L' || n2_cht == 'V')
                return 0;
            mvaddch(game->player1.pos_y + (2 * y), game->player1.pos_x + (2 * x), 'X');
        }
        mvaddch(game->player1.pos_y , game->player1.pos_x, ' ');
        game->player1.pos_x += x;
        game->player1.pos_y += y;
        mvaddch(game->player1.pos_y , game->player1.pos_x, 'P');
    }
    if (type == 'L') {
        char n1_cht = (mvinch(game->player2.pos_y + y, game->player2.pos_x + x) & A_CHARTEXT);
        char n2_cht = (mvinch(game->player2.pos_y + (2 * y), game->player2.pos_x + (2 * x)) & A_CHARTEXT);
        if (n1_cht == '#')
            return 0;
        if (n1_cht == 'X' || n1_cht == 'V') {
            if (n2_cht == '#' || n2_cht == 'X'|| n2_cht == 'P' || n2_cht == 'V')
                return 0;
            mvaddch(game->player2.pos_y + (2 * y), game->player2.pos_x + (2 * x), 'X');
        }
        mvaddch(game->player2.pos_y , game->player2.pos_x, ' ');
        game->player2.pos_x += x;
        game->player2.pos_y += y;
        mvaddch(game->player2.pos_y , game->player2.pos_x, 'L');
    }
}

int update_game(int key_player_client, int key_player_host, game_t *game)
{
    if (key_player_client == KEY_LEFT)
        moves(-1, 0, game, 'L');
    if (key_player_client == KEY_RIGHT)
        moves(1, 0, game, 'L');
    if (key_player_client == KEY_UP)
        moves(0, -1, game, 'L');
    if (key_player_client == KEY_DOWN)
        moves(0, 1, game, 'L');
    
    if (key_player_host == KEY_LEFT)
        moves(-1, 0, game, 'P');
    if (key_player_host == KEY_RIGHT)
        moves(1, 0, game, 'P');
    if (key_player_host == KEY_UP)
        moves(0, -1, game, 'P');
    if (key_player_host == KEY_DOWN)
        moves(0, 1, game, 'P');
    if (key_player_host == 'r') {
        clear();
        game_init(game);
    }
    check_player(game);
    check_o(game->storage);
    check_win(game, game->storage);
    refresh();
}