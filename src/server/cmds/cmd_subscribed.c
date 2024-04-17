/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_subscribed
*/

#include <myteams/logging_server.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <uuid/uuid.h>

#include "cmds/cmds_utils.h"
#include "command.h"
#include "server.h"

static team_t *get_team(server_t *server, client_t *client, char *uuid_str)
{
    uuid_t uuid = {0};
    team_t *team = NULL;

    uuid_parse(uuid_str, uuid);
    team = get_team_by_uuid(server, uuid);
    if (team)
        return team;
    dprintf(client->fd, "511");
    fsync(client->fd);
    write(client->fd, uuid_str, UUID_STR_LEN);
    return NULL;
}

static bool list_teams(const char *buffer)
{
    for (size_t i = 0; buffer[i]; i++) {
        if (buffer[i] != ' ' && buffer[i] != '\t')
            return false;
    }
    return true;
}

static size_t count_teams(server_t *server, client_t *client)
{
    size_t nb = 0;

    for (size_t i = 0; i < server->teams.size; i++) {
        if (user_in_team(client->user->uuid, &server->teams.arr[i]))
            nb += 1;
    }
    return nb;
}

static void list_subscribed_team(server_t *server, client_t *client)
{
    size_t nb = count_teams(server, client);
    team_info_t info = {0};

    dprintf(client->fd, "221");
    fsync(client->fd);
    write(client->fd, &nb, sizeof(nb));
    for (size_t i = 0; i < server->teams.size; i++) {
        if (!user_in_team(client->user->uuid, &server->teams.arr[i]))
            continue;
        write(
            client->fd, team_to_info(&server->teams.arr[i], &info),
            sizeof(team_info_t));
    }
}

static void list_subscribed_users(
    server_t *server, client_t *client, team_t *team)
{
    user_info_t info = {0};

    dprintf(client->fd, "225");
    fsync(client->fd);
    write(client->fd, &team->users.size, sizeof(team->users.size));
    for (size_t i = 0; i < server->users.size; i++) {
        if (!user_in_team(server->users.arr[i].uuid, team))
            continue;
        write(
            client->fd, user_to_info(&server->users.arr[i], &info, team),
            sizeof(user_info_t));
    }
}

void cmd_subscribed(server_t *server, client_t *client)
{
    char *arg = NULL;
    size_t end = 0;
    team_t *team = NULL;

    if (!is_logged_in(client))
        return;
    if (list_teams(client->buffer)) {
        list_subscribed_team(server, client);
        return;
    }
    arg = get_quoted_arg(client->buffer, 0, &end);
    if (arg == NULL) {
        dprintf(client->fd, "502 Syntax error.\n");
        return;
    }
    team = get_team(server, client, arg);
    if (!team)
        return;
    list_subscribed_users(server, client, team);
}
