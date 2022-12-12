/*
** EPITECH PROJECT, 2022
**
** File description:
** sokoban_bonus
*/

#ifndef SOKOBAN_BONUS_H_
    #define SOKOBAN_BONUS_H_

    #include <netinet/in.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <unistd.h>
    #include <stdbool.h>
    #include <arpa/inet.h>
    #include <fcntl.h>
    #include <curses.h>
    #include <ncurses.h>
    #include <sys/select.h>
    #include <sys/stat.h>
    #include "IP_ADRESS.h"

    #define PORT 1515
    #define IP_SERV IP_HOST

    typedef struct socket_s {
        int socketclient;
        int sockethost;
    } socket_t;

    typedef struct storage_s {
        int x;
        int y;
    } storage_t;

    typedef struct player_s {
        int pos_x;
        int pos_y;
    } player_t;

    typedef struct game_s {
        char *buffer;
        player_t player1;
        player_t player2;
        WINDOW *window;
        storage_t **storage;
    } game_t;

    /* CLIENT */
    void create_client(socket_t *sockets);
    void receive_map(socket_t *sockets, game_t *game);
    void client_event_loop(socket_t *sockets, game_t *game);

    /* HOST */
    void create_host(socket_t *sockets);
    void get_map(socket_t *sockets, game_t *game, char *pathfile);
    void host_event_loop(socket_t *sockets, game_t *game);
    
    /* GAME */
    int update_game(int key_player_client, int key_player_host, game_t *game);
    int count_holes(char const *buffer);
    void game_init(game_t *game);
    player_t init_player(char const *buffer, char player_fd);
    storage_t **add_storage(char const *buffer);

    /* ENDGAME */
    void end_game(game_t *game);

#endif /* !SOKOBAN_BONUS_H_ */
