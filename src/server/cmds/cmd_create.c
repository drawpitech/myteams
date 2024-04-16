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

static void create_new_team(
    server_t *server, client_t *client, const char name[],
    const char description[])
{
    team_t new_team = {0};
    char team_uuid_str[37] = {0};
    char client_uuid_str[37] = {0};
    team_info_t info = {0};

    if (!name || !description)
        return;
    strcpy(new_team.name, name);
    strcpy(new_team.description, description);
    uuid_generate(new_team.uuid);
    uuid_unparse(new_team.uuid, team_uuid_str);
    uuid_unparse(client->user->uuid, client_uuid_str);
    append_to_array(&server->teams, sizeof(team_t), &new_team);
    server_event_team_created(team_uuid_str, new_team.name, client_uuid_str);
    team_to_info(&new_team, &info);
    write(client->fd, "211", 3);
    write(client->fd, &info, sizeof(info));
    broadcast(server, "341", &info, sizeof(info));
}

static bool team_already_exist(server_t *server, client_t *client, char *name)
{
    for (size_t i = 0; name && i < server->teams.size; i++) {
        if (strcmp(name, server->teams.arr[i].name) == 0) {
            dprintf(client->fd, "530\n");
            return true;
        }
    }
    return false;
}

static void create_teams(server_t *server, client_t *client)
{
    char *name = NULL;
    char *description = NULL;
    size_t arg_pos = 0;

    name = get_quoted_arg(client->buffer, 0, &arg_pos);
    arg_pos += 1;
    if (name && team_already_exist(server, client, name))
        return;
    if (name) {
        description = get_quoted_arg(client->buffer, arg_pos, &arg_pos);
        if (description) {
            create_new_team(server, client, name, description);
            return;
        }
    }
    dprintf(client->fd, "503 Syntax error.\n");
}

static void create_channel(UNUSED server_t *server, UNUSED client_t *client)
{
    return;
}

static void create_thread(UNUSED server_t *server, UNUSED client_t *client)
{
    return;
}

static void create_reply(UNUSED server_t *server, UNUSED client_t *client)
{
    return;
}

void cmd_create(server_t *server, client_t *client)
{
    if (!server || !client || !is_logged_in(client) || !check_context(client))
        return;
    if (!client->team) {
        create_teams(server, client);
        return;
    }
    if (!client->channel) {
        create_channel(server, client);
        return;
    }
    if (!client->thread) {
        create_thread(server, client);
        return;
    }
    create_reply(server, client);
}
