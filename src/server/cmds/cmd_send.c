/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_send
*/

#include <myteams/logging_client.h>
#include <myteams/logging_server.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <uuid/uuid.h>

#include "cmds/cmds_utils.h"
#include "command.h"
#include "ressources_infos.h"
#include "server.h"
#include "utils.h"

static discussion_t *get_discussion(
    server_t *server, uuid_t uuid1, uuid_t uuid2)
{
    discussion_t *discussion = NULL;
    discussion_t new = {0};

    for (size_t i = 0; i < server->teams.size; i++) {
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

static void send_to_user(server_t *server, message_t *message, uuid_t receive)
{
    message_info_t info = {0};

    uuid_copy(info.sender_uuid, message->sender_uuid);
    info.timestamp = message->timestamp;
    strcpy(info.body, message->body);
    for (size_t i = 0; i < server->clients.size; i++) {
        if (uuid_compare(server->clients.arr[i].user->uuid, receive) == 0) {
            write(server->clients.arr[i].fd, "320", 3);
            write(server->clients.arr[i].fd, &info, sizeof(info));
        }
    }
}

static bool send_message(
    server_t *server, client_t *client, message_t *message, uuid_t uuid)
{
    discussion_t *disc = get_discussion(server, message->sender_uuid, uuid);
    char sender[UUID_STR_LEN] = {0};
    char receiver[UUID_STR_LEN] = {0};

    if (uuid_is_null(disc->user_1uuid) || uuid_is_null(disc->user_2uuid)) {
        uuid_copy(disc->user_1uuid, client->user->uuid);
        uuid_copy(disc->user_2uuid, uuid);
    }
    append_to_array(&disc->messages, sizeof(message_t), message);
    uuid_unparse(client->user->uuid, sender);
    uuid_unparse(uuid, receiver);
    server_event_private_message_sended(sender, receiver, message->body);
    send_to_user(server, message, uuid);
    return true;
}

static bool user_exist(
    server_t *server, client_t *client, uuid_t uuid, char *uuid_str)
{
    if (get_user_by_uuid(server, uuid))
        return true;
    write(client->fd, "514", 3);
    write(client->fd, uuid_str, UUID_STR_LEN);
    return false;
}

static bool get_uuid(
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

static bool create_message(
    server_t *server, client_t *client, uuid_t uuid, size_t *arg_pos)
{
    message_t message = {0};
    char *description = NULL;

    uuid_copy(message.sender_uuid, client->user->uuid);
    message.timestamp = time(NULL);
    description = get_quoted_arg(client->buffer, *arg_pos, arg_pos);
    if (description == NULL) {
        dprintf(client->fd, "502 Syntax error.\n");
        return false;
    }
    strncpy(message.body, description, MAX_BODY_LENGTH);
    send_message(server, client, &message, uuid);
    return true;
}

void cmd_send(server_t *server, client_t *client)
{
    uuid_t uuid = {0};
    size_t arg_pos = 0;

    if (!server || !client || !is_logged_in(client))
        return;
    if (!get_uuid(server, client, &uuid, &arg_pos))
        return;
    if (!create_message(server, client, uuid, &arg_pos))
        return;
}
