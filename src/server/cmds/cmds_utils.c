/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmds_utils
*/

#include "cmds_utils.h"

#include <stddef.h>
#include <string.h>

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

void broadcast(server_t *server, char *code, void *msg, size_t size)
{
    for (size_t i = 0; i < server->clients.size; i++) {
        if (server->clients.arr[i].fd == -1)
            continue;
        write(server->clients.arr[i].fd, code, strlen(code));
        write(server->clients.arr[i].fd, msg, size);
    }
}
