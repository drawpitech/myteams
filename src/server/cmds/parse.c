/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** parse
*/

#include <stddef.h>
#include <string.h>

#include "command.h"

char *get_quoted_arg(char *buff, size_t start, size_t *end)
{
    char *begin = NULL;
    char *end_ptr = NULL;

    if (buff == NULL)
        return NULL;
    buff += start;
    begin = strchr(buff, '"');
    if (begin == NULL)
        return NULL;
    begin += 1;
    end_ptr = strchr(begin, '"');
    if (end_ptr == NULL)
        return NULL;
    *end_ptr = '\0';
    if (end != NULL)
        *end = buff - end_ptr;
    return begin;
}
