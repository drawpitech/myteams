/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_create
*/

#include <myteams/logging_client.h>
#include <myteams/logging_server.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <uuid/uuid.h>

#include "cmds/cmds_utils.h"
#include "command.h"
#include "ressources_infos.h"
#include "server.h"
#include "utils.h"

static void send_to_users(server_t *server, team_t *team, reply_info_t *info)
{
    for (size_t i = 0; i < server->clients.size; i++) {
        if (server->clients.arr[i].fd == -1 ||
            !user_in_team(server->clients.arr[i].user, team))
            continue;
        write(server->clients.arr[i].fd, "344", 3);
        write(server->clients.arr[i].fd, info, sizeof(*info));
    }
}

static void message_user(server_t *server, client_t *client, comment_t *comm)
{
    char thread_uuid[UUID_STR_LEN] = {0};
    char user_uuid[UUID_STR_LEN] = {0};
    user_t *user = get_user_by_uuid(server, client->user);
    team_t *team = get_team_by_uuid(server, client->team);
    channel_t *channel = get_channel_by_uuid(team, client->channel);
    thread_t *thread = get_thread_by_uuid(channel, client->thread);

    uuid_unparse(thread->thread_uuid, thread_uuid);
    uuid_unparse(user->uuid, user_uuid);
    server_event_reply_created(thread_uuid, user_uuid, comm->message);
}

static void create_new_reply(
    server_t *server, client_t *client, const char body[])
{
    comment_t comment = {0};
    reply_info_t info = {0};
    team_t *team = get_team_by_uuid(server, client->team);
    channel_t *channel = get_channel_by_uuid(team, client->channel);
    thread_t *thread = get_thread_by_uuid(channel, client->thread);

    if (body == NULL)
        return;
    uuid_copy(comment.author_uuid, client->user);
    strcpy(comment.message, body);
    append_to_array(&thread->comments, sizeof comment, &comment);
    write(client->fd, "214", 3);
    comment_to_info(&comment, &info, thread, team);
    write(client->fd, &info, sizeof info);
    message_user(server, client, &comment);
    send_to_users(server, team, &info);
}

static void create_reply(UNUSED server_t *server, UNUSED client_t *client)
{
    char *body = NULL;
    size_t arg_pos = 0;

    body = get_quoted_arg(client->buffer, 0, &arg_pos);
    if (!body) {
        dprintf(client->fd, "502 Syntax error.\n");
        return;
    }
    create_new_reply(server, client, body);
}

void cmd_create(server_t *server, client_t *client)
{
    if (!server || !client || !is_logged_in(client) || !check_context(client))
        return;
    if (uuid_is_null(client->team)) {
        create_teams(server, client);
        return;
    }
    if (!user_in_team(client->user, get_team_by_uuid(server, client->team))) {
        dprintf(client->fd, "520");
        return;
    }
    if (uuid_is_null(client->channel))
        create_channel(server, client);
    else if (uuid_is_null(client->thread))
        create_thread(server, client);
    else
        create_reply(server, client);
}
