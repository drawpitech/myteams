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

static bool send_unknow_error(client_t *client, char type, uuid_t uuid)
{
    char uuid_str[37] = {0};

    uuid_unparse(uuid, uuid_str);
    write(client->fd, "51", 2);
    write(client->fd, &type, 1);
    write(client->fd, uuid_str, sizeof(uuid_str));
    DEBUG("send 51%c\n <uid> to user", type);
    return false;
}

bool check_context(client_t *client)
{
    if (!client->team) {
        if (!uuid_is_null(client->uuid.team))
            return true;
        return send_unknow_error(client, '1', client->uuid.team);
    }
    if (!client->channel) {
        if (!uuid_is_null(client->uuid.channel))
            return true;
        return send_unknow_error(client, '2', client->uuid.channel);
    }
    if (!client->thread) {
        if (!uuid_is_null(client->uuid.thread))
            return true;
        return send_unknow_error(client, '3', client->uuid.thread);
    }
    return true;
}
