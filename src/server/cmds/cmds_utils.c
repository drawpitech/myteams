/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmds_utils
*/

#include "cmds_utils.h"
#include "debug.h"
#include "server.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <uuid/uuid.h>

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
    if (server == NULL || code == NULL || msg == NULL)
        return;
    DEBUG_MSG("Broadcasting message");
    for (size_t i = 0; i < server->clients.size; i++) {
        if (server->clients.arr[i].fd == -1)
            continue;
        DEBUG("Broadcasting to fd %d", server->clients.arr[i].fd);
        write(server->clients.arr[i].fd, code, strlen(code));
        write(server->clients.arr[i].fd, msg, size);
    }
}

bool user_in_team(uuid_t uuid, team_t *team)
{
    if (team == NULL)
        return false;
    for (size_t i = 0; i < team->users.size; i++) {
        if (uuid_compare(team->users.arr[i], uuid) == 0)
            return true;
    }
    return false;
}

bool is_logged_in(client_t *client)
{
    if (client == NULL)
        return false;
    if (uuid_is_null(client->user)) {
        dprintf(client->fd, "520");
        return false;
    }
    return true;
}

static bool send_unknow_error(client_t *client, char type, uuid_t uuid)
{
    char uuid_str[UUID_STR_LEN] = {0};

    uuid_unparse(uuid, uuid_str);
    dprintf(client->fd, "51%c", type);
    fsync(client->fd);
    write(client->fd, uuid_str, sizeof(uuid_str));
    DEBUG("send 51%c <uid> to user", type);
    return false;
}

static bool uuid_is_invalid(uuid_t uuid)
{
    return uuid_compare(uuid, INVALID_UUID) == 0;
}

bool check_context(client_t *client)
{
    if (client == NULL)
        return false;
    if (uuid_is_null(client->team)) {
        if (uuid_is_invalid(client->team))
            return send_unknow_error(client, '1', client->team);
        return true;
    }
    if (uuid_is_null(client->channel)) {
        if (uuid_is_invalid(client->channel))
            return send_unknow_error(client, '2', client->channel);
        return true;
    }
    if (uuid_is_null(client->thread)) {
        if (uuid_is_invalid(client->thread))
            return send_unknow_error(client, '3', client->thread);
        return true;
    }
    return true;
}
