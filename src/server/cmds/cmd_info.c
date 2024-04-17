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

static void info_team(client_t *client)
{
    team_info_t info = {0};

    dprintf(client->fd, "211");
    fsync(client->fd);
    write(client->fd, team_to_info(client->team, &info), sizeof(info));
}

static void info_channel(client_t *client)
{
    channel_info_t info = {0};

    dprintf(client->fd, "212");
    fsync(client->fd);
    write(client->fd, channel_to_info(client->channel, &info), sizeof(info));
}

static void info_thread(client_t *client)
{
    thread_info_t info = {0};

    dprintf(client->fd, "213");
    fsync(client->fd);
    write(client->fd, thread_to_info(client->thread, &info), sizeof(info));
}

static void info_user(client_t *client)
{
    user_info_t info = {0};

    printf("send user info\n");
    dprintf(client->fd, "215");
    fsync(client->fd);
    write(
        client->fd, user_to_info(client->user, &info, client->team),
        sizeof(info));
}

void cmd_info(server_t *server, client_t *client)
{
    if (!server || !client || !is_logged_in(client) || !check_context(client))
        return;
    if (!client->team) {
        info_user(client);
        return;
    }
    if (!user_in_team(client->user->uuid, client->team)) {
        dprintf(client->fd, "520");
        return;
    }
    if (!client->channel) {
        info_team(client);
        return;
    }
    if (!client->thread) {
        info_channel(client);
        return;
    }
    info_thread(client);
}
