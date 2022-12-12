/*
** EPITECH PROJECT, 2022
** bonus-sokoban
** File description:
** peer
*/

#include "sokoban_bonus.h"

void display_help_menu(void)
{
    printf("HELP MENU: (-h)\n");
    printf("\n    USAGE:\n");
    printf("        LAUNCH GAME:\n");
    printf("            ./my_sokoban_lan [STATUS] [MAP_FILEPATH]*\n");
    printf("            *HOST ENTERS THE FILEPATH\n");
    printf("            HOST : ./my_sokoban_lan HOST test2.txt\n");
    printf("            CLIENT : ./my_sokoban_lan CLIENT\n");
    printf("        HOW TO PLAY:\n");
    printf("            [^] [v] [<] [>]\n");
    printf("            -Keyboard Arrows to move\n");
    printf("            [r]\n");
    printf("            -Restart the map (host only)\n");
    printf("        INFOS:\n");
    printf("            2-Players Game\n");
    printf("            Player 1: L (host)\n");
    printf("            Player 2: P (client)\n");
    printf("\n    CUSTOMIZATION:\n");
    printf("        LAN GAME:\n");
    printf("            You may play with your friend on 2 different computers\n");
    printf("            Step 1: (As the host) please lower your firewall using the command:\n");
    printf("            $sudo systemctl stop firewalld\n");
    printf("            Step 2: (As the host) please find your netword IP ADRESS\n");
    printf("            Step 3: (As the client) please modify the IP_ADRESS.h file\n");
    printf("            (l.17) IP_HOST 'XXX.XXX.XXX.XXX'\n");
    printf("            -> Replace the 'XXX.XXX.XXX.XXX' by the host IP_ADRESS\n");
    printf("            Step 4: (as host and client) Launch the game and enjoy\n");
    printf("        MAP_CREATION:\n");
    printf("            You may create your own maps to play with your friends\n");
    printf("            Don't forget to place a player L and a player P\n");
    printf("\n    CREDITS:\n");
    printf("        SAUTRON LEO & GROSSET Pierre-Alexandre\n");
    printf("            With the support of the ETIB-CORP\n");
    printf("            1st-year EPITECH STUDENTS\n");
    printf("            1st-time experimenting with network communications\n");
    exit(0);
}

void end_game(game_t *game)
{
    //free(game->buffer);
    for (int i = 0; game->storage[i] != NULL; i++)
        free(game->storage[i]);
    free(game->storage);
    endwin();
    exit(0);
}

int main(int ac, char **av)
{
    socket_t sockets = {0};
    game_t game = {0};
    if (strcmp(av[1], "-h") == 0 || ac == 1) {
        display_help_menu();
    } else if (strcmp(av[1], "HOST") == 0) {
        create_host(&sockets);
        get_map(&sockets, &game, av[2]);
        game_init(&game);
        host_event_loop(&sockets, &game);
    } else if (strcmp(av[1], "CLIENT") == 0) {
        create_client(&sockets);
        receive_map(&sockets, &game);
        game_init(&game);
        client_event_loop(&sockets, &game);
    } else {
        perror("PLEASE ENTER VALID STATUS\n");
        exit(84);
    }
    end_game(&game);
    return 0;
}