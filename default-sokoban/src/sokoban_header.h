/*
** EPITECH PROJECT, 2022
** B-PSU-100-RUN-1-1-sokoban-pierre-alexandre.grosset
** File description:
** sokoban_header
*/

#ifndef SOKOBAN_HEADER_H_
    #define SOKOBAN_HEADER_H_

    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <stdlib.h>
    #include <ncurses.h>

    #define HM_US0 "USAGE"
    #define HM_US1 "./my_sokoban map"
    #define HM_DE0 "DESCRIPTION"
    #define HM_DE1 "map file representing the warehouse"
    #define HM_DE2 " map, containing ‘#’ for walls,"
    #define HM_DE3 "‘P’ for the player, ‘X’ for boxes"
    #define HM_DE4 " and ‘O’ for storage locations."

    #define VALID_CHAR_SOKOBAN " \n#XOP"
    #define VALID_MOVE "1234"


    typedef struct valid_checker_s {
        int X_amount;
        int O_amount;
        int P_amount;
    } valid_checker_t;

    typedef struct storage_s {
        int x;
        int y;
    } storage_t;

    typedef struct player_s {
        int pos_x;
        int pos_y;
    } player_t;

    player_t init_player(char const *buffer);
    int count_holes(char const *buffer);
    storage_t **add_storage(char const *buffer);
    void loop(char const *buffer, player_t player, storage_t **storage);
    int process(char const *buffer);
    int is_token(char const c, char const *const tokens);
    int my_strcmp(char const *str1, char const *str2);
    int event_handler(int key);
    void moves(player_t *player, int x, int y);
    void check_o(storage_t **storage);
    int my_strlen(char *str);
    int display_help_menu(void);
    int map_validity_checker(char const *buffer);
    int map_content_checker(char *pathfile);
    int map_opening_checker(char *pathfile);

#endif /* !SOKOBAN_HEADER_H_ */
