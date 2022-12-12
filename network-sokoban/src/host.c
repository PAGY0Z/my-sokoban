/*
** EPITECH PROJECT, 2022
** bonus-sokoban
** File description:
** host
*/

#include "sokoban_bonus.h"

void create_host(socket_t *sockets)
{
    sockets->sockethost = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in peer_adress;
    peer_adress.sin_addr.s_addr = INADDR_ANY;
    peer_adress.sin_family = AF_INET;
    peer_adress.sin_port = htons(PORT);
    int opt = 1;
    int peer_adress_len = sizeof(peer_adress);
    if (setsockopt(sockets->sockethost, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        perror("SETSOCKET FAILED\n");
        exit(84);
    }
    if (bind(sockets->sockethost, (struct sockaddr*)&peer_adress, sizeof(peer_adress)) < 0) {
        perror("FAILED TO BIND\n");
        exit(84);
    }
    if (listen(sockets->sockethost, SOMAXCONN) == -1) {
        perror("FAILED TO LISTEN\n");
        exit(84);
    }
    if ((sockets->socketclient = accept(sockets->sockethost, (struct sockaddr*)&peer_adress, (socklen_t *)&peer_adress_len)) < 0) {
        perror("CONNECTION FAILED\n");
        exit(84);
    }
    printf("CLIENT CONNECT\n");
}

void get_map(socket_t *sockets, game_t *game, char *pathfile)
{
    struct stat statement;
    int fd;
    ssize_t len = 0;
    ssize_t bytes = 0;

    if (stat(pathfile, &statement) == -1) {
        perror("FAILED TO INIT STATS\n");
        exit(84);
    }
    if (S_ISREG(statement.st_mode) == false || statement.st_size == 0) {
        perror("FILE NOT FILE OR EMPTY\n");
        exit(84);
    }
    if ((fd = open(pathfile, O_RDONLY)) == -1) {
        perror("FAILED TO OPEN/FIND FILE\n");
        exit(84);
    }
    game->buffer = malloc(sizeof(char) * (statement.st_size + 1));
    if (read(fd, game->buffer, statement.st_size) == -1) {
        perror("FAILED TO READ\n");
        exit(84);
    }
    game->buffer[statement.st_size] = '\0';
    if (send(sockets->socketclient, &statement.st_size, sizeof(statement.st_size), 0) != sizeof(statement.st_size)) {
        perror("FAILED TO SEND SIZE\n");
        exit(84);
    }
    while ((bytes = send(sockets->socketclient, game->buffer, statement.st_size - len, 0)) > 0) {
        len += bytes;
        game->buffer += bytes;
        if (bytes < 0 ) {
            perror("FAILED TO SEND BUFFER\n");
            exit(84);
        }
    }
    game->buffer -= len;
}

void host_event_loop(socket_t *sockets, game_t *game)
{
    int key_player_host = 0;
    int key_player_client = 0;
    fd_set current_sockets, ready_sockets;

    FD_ZERO(&current_sockets);
    FD_ZERO(&ready_sockets);
    FD_SET(sockets->socketclient, &current_sockets);
    FD_SET(0, &current_sockets);

    refresh();
    while (true) {
        memcpy(&ready_sockets, &current_sockets, sizeof(fd_set));
        if ((select(SOMAXCONN, &ready_sockets, NULL, NULL, NULL)) < 0) {
            perror("SELECT ERROR\n");
            break;
        }
        /* HOST INPUT */
        if (FD_ISSET(0, &ready_sockets)) {
            key_player_host = getch();
            if (key_player_host == ' ')
                break;
            if (send(sockets->socketclient, &key_player_host, sizeof(int), 0) <= 0)
                break;
        }
        /* CLIENT INPUT */
        if (FD_ISSET(sockets->socketclient, &ready_sockets)) {
            if (read(sockets->socketclient, &key_player_client, sizeof(int)) <= 0)
                break;
            if (key_player_client == -1)
                break;
        }
        update_game(key_player_client, key_player_host, game);
        key_player_client = 0;
        key_player_host = 0;
    }
}