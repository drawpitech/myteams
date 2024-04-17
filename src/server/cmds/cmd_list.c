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
    write(client->fd, &server->teams.size, sizeof(server->teams.size));
    for (size_t i = 0; i < server->teams.size; i++) {
        write(
            client->fd, team_to_info(&server->teams.arr[i], &info),
            sizeof(team_info_t));
    }
}

static void list_channels(client_t *client, team_t *team)
{
    channel_info_t info = {0};

    dprintf(client->fd, "222");
    fsync(client->fd);
    write(client->fd, &team->channels.size, sizeof(team->channels.size));
    for (size_t i = 0; i < team->channels.size; i++) {
        write(
            client->fd, channel_to_info(&team->channels.arr[i], &info),
            sizeof(info));
    }
}

static void list_threads(client_t *client, channel_t *channel)
{
    thread_info_t info = {0};

    dprintf(client->fd, "223");
    fsync(client->fd);
    write(client->fd, &channel->threads.size, sizeof(channel->threads.size));
    for (size_t i = 0; i < channel->threads.size; i++) {
        write(
            client->fd, thread_to_info(&channel->threads.arr[i], &info),
            sizeof(info));
    }
}

static void list_replies(client_t *client, thread_t *thread, team_t *team)
{
    reply_info_t info = {0};

    dprintf(client->fd, "224");
    fsync(client->fd);
    write(client->fd, &thread->comments.size, sizeof(thread->comments.size));
    for (size_t i = 0; i < thread->comments.size; i++) {
        write(
            client->fd,
            comment_to_info(&thread->comments.arr[i], &info, thread, team),
            sizeof(info));
    }
}

void cmd_list(server_t *server, client_t *client)
{
    if (!server || !client || !is_logged_in(client) || !check_context(client))
        return;
    if (!client->team) {
        list_teams(server, client);
        return;
    }
    if (!user_in_team(client, client->team)) {
        dprintf(client->fd, "520");
        return;
    }
    if (!client->channel) {
        list_channels(client, client->team);
        return;
    }
    if (!client->thread) {
        list_threads(client, client->channel);
        return;
    }
    list_replies(client, client->thread, client->team);
}
