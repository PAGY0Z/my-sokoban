/*
** EPITECH PROJECT, 2022
** my_sokoban Written by GROSSET Pierre-Alexandre
** File description:
** Main file, opening file, error handling, help menu
*/

#include "sokoban_header.h"
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc == 2)
        return map_opening_checker(argv[1]);
    else {
        write(2, "WRONG ARGUMENTS NUMBER", 23);
        return 84;
    }
    return 84;
}
