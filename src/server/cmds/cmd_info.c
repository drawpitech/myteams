/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_info
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

static void info_team(server_t *server, client_t *client)
{
    team_info_t info = {0};
    team_t *team = get_team_by_uuid(server, client->team);

    dprintf(client->fd, "211");
    fsync(client->fd);
    write(client->fd, team_to_info(team, &info), sizeof info);
}

static void info_channel(server_t *server, client_t *client)
{
    channel_info_t info = {0};
    team_t *team = get_team_by_uuid(server, client->team);
    channel_t *channel = get_channel_by_uuid(team, client->channel);

    dprintf(client->fd, "212");
    fsync(client->fd);
    write(client->fd, channel_to_info(channel, &info), sizeof info);
}

static void info_thread(server_t *server, client_t *client)
{
    thread_info_t info = {0};
    team_t *team = get_team_by_uuid(server, client->team);
    channel_t *channel = get_channel_by_uuid(team, client->channel);
    thread_t *thread = get_thread_by_uuid(channel, client->thread);

    dprintf(client->fd, "213");
    fsync(client->fd);
    write(client->fd, thread_to_info(thread, &info), sizeof info);
}

static void info_user(server_t *server, client_t *client)
{
    user_info_t info = {0};
    user_t *user = get_user_by_uuid(server, client->user);
    team_t *team = get_team_by_uuid(server, client->team);

    dprintf(client->fd, "215");
    fsync(client->fd);
    write(client->fd, user_to_info(user, &info, team), sizeof info);
}

void cmd_info(server_t *server, client_t *client)
{
    if (!server || !client || !is_logged_in(client) || !check_context(client))
        return;
    if (uuid_is_null(client->team)) {
        info_user(server, client);
        return;
    }
    if (!user_in_team(client->user, get_team_by_uuid(server, client->team))) {
        dprintf(client->fd, "520");
        return;
    }
    if (uuid_is_null(client->channel)) {
        info_team(server, client);
        return;
    }
    if (uuid_is_null(client->thread)) {
        info_channel(server, client);
        return;
    }
    info_thread(server, client);
}
