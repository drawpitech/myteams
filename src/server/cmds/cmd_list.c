/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_list
*/

#include <myteams/logging_client.h>
#include <myteams/logging_server.h>
#include <stdio.h>
#include <unistd.h>
#include <uuid/uuid.h>

#include "cmds/cmds_utils.h"
#include "command.h"
#include "ressources_infos.h"
#include "server.h"

static void list_teams(server_t *server, client_t *client)
{
    team_info_t info = {0};

    dprintf(client->fd, "221");
    fsync(client->fd);
    WRITE(client->fd, server->teams.size);
    for (size_t i = 0; i < server->teams.size; i++)
        WRITE(client->fd, *team_to_info(&server->teams.arr[i], &info));
}

static void list_channels(server_t *server, client_t *client)
{
    team_t *team = get_team_by_uuid(server, client->team);
    channel_info_t info = {0};

    if (team == NULL)
        return;
    dprintf(client->fd, "222");
    fsync(client->fd);
    WRITE(client->fd, team->channels.size);
    for (size_t i = 0; i < team->channels.size; i++)
        WRITE(client->fd, *channel_to_info(&team->channels.arr[i], &info));
}

static void list_threads(server_t *server, client_t *client)
{
    thread_info_t info = {0};
    channel_t *channel = get_channel_by_uuid(
        get_team_by_uuid(server, client->team), client->channel);

    dprintf(client->fd, "223");
    fsync(client->fd);
    WRITE(client->fd, channel->threads.size);
    for (size_t i = 0; i < channel->threads.size; i++)
        WRITE(client->fd, *thread_to_info(&channel->threads.arr[i], &info));
}

static void list_replies(server_t *server, client_t *client)
{
    reply_info_t info = {0};
    team_t *team = get_team_by_uuid(server, client->team);
    channel_t *channel = get_channel_by_uuid(team, client->channel);
    thread_t *thread = get_thread_by_uuid(channel, client->thread);

    dprintf(client->fd, "224");
    fsync(client->fd);
    WRITE(client->fd, thread->comments.size);
    for (size_t i = 0; i < thread->comments.size; i++)
        WRITE(
            client->fd,
            *comment_to_info(&thread->comments.arr[i], &info, thread, team));
}

void cmd_list(server_t *server, client_t *client)
{
    if (!server || !client || !is_logged_in(client) || !check_context(client))
        return;
    if (uuid_is_null(client->team)) {
        list_teams(server, client);
        return;
    }
    if (!user_in_team(client->user, get_team_by_uuid(server, client->team))) {
        dprintf(client->fd, "520");
        return;
    }
    if (uuid_is_null(client->channel)) {
        list_channels(server, client);
        return;
    }
    if (uuid_is_null(client->thread)) {
        list_threads(server, client);
        return;
    }
    list_replies(server, client);
}
