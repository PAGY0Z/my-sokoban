/*
** EPITECH PROJECT, 2022
** bonus-sokoban
** File description:
** client
*/

#include "sokoban_bonus.h"

void create_client(socket_t *sockets)
{
    sockets->sockethost = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in peer_adress;
    peer_adress.sin_family = AF_INET;
    peer_adress.sin_port = htons(PORT);
    
    if (inet_pton(AF_INET, IP_SERV, &peer_adress.sin_addr) < 0) {
        perror("INVALID ADDRESS\n");
        exit(84);
    }
    int check = 0;
    while ((sockets->socketclient = connect(sockets->sockethost, (struct sockaddr*)&peer_adress, sizeof(struct sockaddr_in))) == -1) {
        if (check == 0) {
            check = 1;
            printf("CONNECTION WAITING\n[...]\n");
        }
        if (sockets->socketclient != -1)
            break;
    }
    printf("CLIENT CONNECT\n");
}

void receive_map(socket_t *sockets, game_t *game)
{
    //endwin();
    struct stat st;
    ssize_t bytes = 0;
    ssize_t len = 0;

    read(sockets->sockethost, &st.st_size, sizeof(st.st_size));
    game->buffer = malloc(sizeof(char) * (st.st_size + 1));
    while((bytes = read(sockets->sockethost, game->buffer, st.st_size - len)) > 0) {
        len += bytes;
        game->buffer += bytes;
    }
    game->buffer -= len;
    game->buffer[st.st_size] = '\0';
}

void client_event_loop(socket_t *sockets, game_t *game)
{
    int key_player_host = 0;
    int key_player_client = 0;
    fd_set current_sockets, ready_sockets;

    FD_ZERO(&current_sockets);
    FD_SET(sockets->sockethost, &current_sockets);
    FD_SET(0, &current_sockets);

    while (true) {
        memcpy(&ready_sockets, &current_sockets, sizeof(fd_set));
        if ((select(SOMAXCONN, &ready_sockets, NULL, NULL, NULL)) < 0) {
            perror("SELECT ERROR\n");
            break;
        }
        /* CLIENT INPUT */
        if (FD_ISSET(0, &ready_sockets)) {
            key_player_client = getch();
            if (key_player_client == ' ')
                break;
            if (send(sockets->sockethost, &key_player_client, sizeof(int), 0) <= 0)
                break;
        }
        /* HOST INPUT */
        if (FD_ISSET(sockets->sockethost, &ready_sockets)) {
            if (read(sockets->sockethost, &key_player_host, sizeof(int)) <= 0)
                break;
            if (key_player_host == -1)
                break;
        }
        update_game(key_player_client, key_player_host, game);
        key_player_client = 0;
        key_player_host = 0;
    }
}
