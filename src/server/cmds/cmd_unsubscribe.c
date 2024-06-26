/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_unsubscribe
*/

#include <myteams/logging_server.h>
#include <string.h>
#include <sys/types.h>
#include <uuid/uuid.h>

#include "cmds/cmds_utils.h"
#include "command.h"
#include "ressources_infos.h"
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

static void send_message(server_t *server, client_t *client, team_t *team)
{
    user_info_t info = {0};
    char team_uuid[UUID_STR_LEN] = {0};
    char user_uuid[UUID_STR_LEN] = {0};
    user_t *user = get_user_by_uuid(server, client->user);

    if (user == NULL)
        return;
    uuid_unparse(client->user, user_uuid);
    uuid_unparse(team->uuid, team_uuid);
    server_event_user_unsubscribed(team_uuid, user_uuid);
    write(client->fd, "215", 3);
    write(client->fd, user_to_info(user, &info, team), sizeof info);
}

static void remove_user(client_t *client, team_t *team)
{
    for (size_t i = 0; i < team->users.size; i++) {
        if (uuid_compare(client->user, team->users.arr[i]) == 0) {
            uuid_copy(
                team->users.arr[i], team->users.arr[team->users.size - 1]);
            team->users.size -= 1;
            return;
        }
    }
}

void cmd_unsubscribe(server_t *server, client_t *client)
{
    char *arg = NULL;
    team_t *team = NULL;

    if (!is_logged_in(client))
        return;
    arg = get_quoted_arg(client->buffer, 0, NULL);
    if (arg == NULL) {
        dprintf(client->fd, "502 Syntax error.\n");
        return;
    }
    team = get_team(server, client, arg);
    if (team == NULL || !user_in_team(client->user, team))
        return;
    remove_user(client, team);
    send_message(server, client, team);
}
