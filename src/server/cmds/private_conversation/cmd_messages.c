/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_messages
*/

#include <myteams/logging_client.h>
#include <myteams/logging_server.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <uuid/uuid.h>

#include "cmds/cmds_utils.h"
#include "command.h"
#include "private_parts.h"
#include "ressources_infos.h"
#include "server.h"

static discussion_t *get_conv(server_t *server, uuid_t uuid1, uuid_t uuid2)
{
    discussion_t *discussion = NULL;

    for (size_t i = 0; i < server->discussions.size; i++) {
        discussion = &server->discussions.arr[i];
        if ((uuid_compare(discussion->user_1uuid, uuid1) == 0 &&
                uuid_compare(discussion->user_2uuid, uuid2) == 0) ||
                (uuid_compare(discussion->user_1uuid, uuid2) == 0 &&
                uuid_compare(discussion->user_2uuid, uuid1) == 0))
            return discussion;
    }
    return NULL;
}

static void send_list(client_t *client, discussion_t *discussion)
{
    message_info_t info = {0};
    message_t *mess = NULL;

    dprintf(client->fd, "226");
    fsync(client->fd);
    write(client->fd,
        &discussion->messages.size, sizeof(discussion->messages.size));
    for (size_t i = 0; i < discussion->messages.size; i++) {
        mess = &discussion->messages.arr[i];
        uuid_copy(info.sender_uuid, mess->sender_uuid);
        info.timestamp = mess->timestamp;
        strncpy(info.body, mess->body, MAX_BODY_LENGTH);
        write(client->fd, &info, sizeof(info));
    }
}

void cmd_messages(server_t *server, client_t *client)
{
    uuid_t uuid = {0};
    size_t arg_pos = 0;
    discussion_t *discussion = NULL;

    if (!server || !client || !is_logged_in(client))
        return;
    if (!get_uuid(server, client, &uuid, &arg_pos))
        return;
    discussion = get_conv(server, client->user, uuid);
    if (!discussion)
        return;
    printf("fjdhskfhsdkj\n");
    send_list(client, discussion);
}
