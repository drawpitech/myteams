/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** parse
*/

#include "command.h"
#include <stddef.h>

char *get_arg(char *buff, int start, int *end)
{
    int i = start;
    int j = 0;

    if (!buff)
        return NULL;
    while (buff[i] && buff[i] != '"')
        i ++;
    if (buff[i] == '\0' || buff[i + 1] == '\0')
        return NULL;
    i ++;
    while (buff[i + j] && buff[i + j] != '"')
        j ++;
    if (buff[i + j] == '\0')
        return NULL;
    buff[i + j] = '\0';
    *end = i + j;
    return buff + i;
}
