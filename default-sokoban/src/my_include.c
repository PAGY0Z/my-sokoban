/*
** EPITECH PROJECT, 2022
** B-PSU-100-RUN-1-1-sokoban-pierre-alexandre.grosset
** File description:
** my_strcmp
*/

int is_token(char const c, char const *const tokens)
{
    for (int i = 0; tokens[i] != '\0'; i++){
        if (c == tokens[i])
            return 1;
    }
    return 0;
}

int my_strcmp(char const *str1, char const *str2)
{
    for (int i = 0; str1[i]; i++) {
        if (str1[i] != str2[i])
            return 1;
    }
    return 0;
}
