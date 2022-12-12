/*
** EPITECH PROJECT, 2022
** B-PSU-100-RUN-1-1-sokoban-pierre-alexandre.grosset
** File description:
** validity
*/

#include "sokoban_header.h"

int my_strlen(char *str)
{
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

int display_help_menu(void)
{
    write(1, HM_US0, my_strlen(HM_US0));
    write(1, HM_US1, my_strlen(HM_US1));
    write(1, HM_DE0, my_strlen(HM_DE0));
    write(1, HM_DE1, my_strlen(HM_DE1));
    write(1, HM_DE2, my_strlen(HM_DE2));
    write(1, HM_DE3, my_strlen(HM_DE3));
    write(1, HM_DE4, my_strlen(HM_DE4));
    return 0;
}

int map_validity_checker(char const *buffer)
{
    valid_checker_t valid_log = {0};
    for (int i = 0; buffer[i]; i++) {
        if (!(is_token(buffer[i], VALID_CHAR_SOKOBAN))) {
            write(2, "INVALID CHAR DETECTED", 22);
            return 84;
        }
        if (buffer[i] == 'P')
            valid_log.P_amount++;
        if (buffer[i] == 'O')
            valid_log.O_amount++;
        if (buffer[i] == 'X')
            valid_log.X_amount++;
    }
    if (valid_log.O_amount != valid_log.X_amount || valid_log.P_amount != 1) {
        write(2, "WRONG NUMBER OF BOXES/HOLES/PLAYER", 35);
        return 84;
    }
    return process(buffer);
}

int map_content_checker(char *pathfile)
{
    int fd = open(pathfile, O_RDONLY);
    char *buffer;
    struct stat statement;
    stat(pathfile, &statement);
    if (statement.st_size == 0) {
        write(2, "INVALID FILE SIZE", 18);
        close(fd);
        return 84;
    }
    buffer = malloc(sizeof(char) * statement.st_size);
    read(fd, buffer, statement.st_size);
    close(fd);
    return map_validity_checker(buffer);
}

int map_opening_checker(char *pathfile)
{
    int fd;
    if (my_strcmp(pathfile, "-h") == 0)
        return display_help_menu();
    if ((fd = open(pathfile, O_RDONLY)) == -1) {
        write(2, "FILE NOT FOUND", 15);
        close(fd);
        return 84;
    }
    if ((fd = open(pathfile, O_RDONLY)) != -1) {
        close(fd);
        return map_content_checker(pathfile);
    }
    return 84;
}
