/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** private_parts
*/

#include "private_parts.h"
#include "cmds/cmds_utils.h"
#include "server.h"
#include <uuid/uuid.h>

discussion_t *get_discussion(
    server_t *server, uuid_t uuid1, uuid_t uuid2)
{
    discussion_t *discussion = NULL;
    discussion_t new = {0};

    for (size_t i = 0; i < server->discussions.size; i++) {
        discussion = &server->discussions.arr[i];
        if ((uuid_compare(discussion->user_1uuid, uuid1) == 0 &&
                uuid_compare(discussion->user_2uuid, uuid2) == 0) ||
                (uuid_compare(discussion->user_1uuid, uuid2) == 0 &&
                uuid_compare(discussion->user_2uuid, uuid1) == 0))
            return discussion;
    }
    append_to_array(&server->discussions, sizeof(discussion_t), &new);
    return &server->discussions.arr[server->discussions.size - 1];
}

bool user_exist(
    server_t *server, client_t *client, uuid_t uuid, char *uuid_str)
{
    if (get_user_by_uuid(server, uuid))
        return true;
    write(client->fd, "514", 3);
    write(client->fd, uuid_str, UUID_STR_LEN);
    return false;
}

bool get_uuid(
    server_t *server, client_t *client, uuid_t *uuid, size_t *arg_pos)
{
    char *arg1 = NULL;

    arg1 = get_quoted_arg(client->buffer, 0, arg_pos);
    if (!arg1) {
        dprintf(client->fd, "502 Syntax error.\n");
        return false;
    }
    *arg_pos += 1;
    uuid_parse(arg1, *uuid);
    return user_exist(server, client, *uuid, arg1);
}
