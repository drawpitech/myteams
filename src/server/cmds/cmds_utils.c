/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmds_utils
*/

#include "cmds_utils.h"

#include "server.h"
#include <stddef.h>
#include <string.h>
#include "ressources_infos.h"

char *get_quoted_arg(char *buff, size_t start, size_t *end)
{
    char *begin = NULL;
    char *end_ptr = NULL;

    if (buff == NULL)
        return NULL;
    begin = strchr(buff + start, '"');
    if (begin == NULL)
        return NULL;
    begin += 1;
    end_ptr = strchr(begin, '"');
    if (end_ptr == NULL)
        return NULL;
    *end_ptr = '\0';
    if (end != NULL)
        *end = end_ptr - buff;
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

bool is_logged_in(client_t *client)
{
    if (!client->user) {
        dprintf(client->fd, "520\n");
        return false;
    }
    return true;
}

user_info_t *user_to_info(user_t *user, user_info_t *info)
{
    if (user == NULL || info == NULL)
        return NULL;
    memset(info, 0, sizeof *info);
    strcpy(info->name, user->name);
    uuid_copy(info->user_uuid, user->uuid);
    return info;
}

team_info_t *team_to_info(team_t *team, team_info_t *info)
{
    if (team == NULL || info == NULL)
        return NULL;
    memset(info, 0, sizeof *info);
    strcpy(info->description, team->description);
    strcpy(info->name, team->name);
    uuid_copy(info->uuid, team->uuid);
    return info;
}
