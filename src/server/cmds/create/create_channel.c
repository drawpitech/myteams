/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** create_channel
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

static void send_to_users(server_t *server, team_t *team, channel_info_t *info)
{
    for (size_t i = 0; i < server->clients.size; i++) {
        if (server->clients.arr[i].fd == -1 ||
            !user_in_team(&server->clients.arr[i], team))
            continue;
        write(server->clients.arr[i].fd, "342", 3);
        write(server->clients.arr[i].fd, info, sizeof(*info));
    }
}

static void create_new_channel(
    server_t *server, client_t *client, const char name[],
    const char description[])
{
    channel_t new_chan = {0};
    char chan_uuid[UUID_STR_LEN] = {0};
    char team_uuid[UUID_STR_LEN] = {0};
    channel_info_t info = {0};

    if (!name || !description)
        return;
    strcpy(new_chan.name, name);
    strcpy(new_chan.description, description);
    uuid_generate(new_chan.uuid);
    uuid_unparse(new_chan.uuid, chan_uuid);
    uuid_unparse(client->team->uuid, team_uuid);
    append_to_array(&client->team->channels, sizeof(channel_t), &new_chan);
    server_event_channel_created(team_uuid, chan_uuid, new_chan.name);
    write(client->fd, "212", 3);
    write(client->fd, channel_to_info(&new_chan, &info), sizeof(info));
    send_to_users(server, client->team, &info);
}

static bool channel_already_exist(team_t *team, client_t *client, char *name)
{
    for (size_t i = 0; name && i < team->channels.size; i++) {
        if (strcmp(name, team->channels.arr[i].name) == 0) {
            dprintf(client->fd, "530\n");
            return true;
        }
    }
    return false;
}

void create_channel(server_t *server, client_t *client)
{
    char *name = NULL;
    char *description = NULL;
    size_t arg_pos = 0;

    name = get_quoted_arg(client->buffer, 0, &arg_pos);
    arg_pos += 1;
    if (name && channel_already_exist(client->team, client, name))
        return;
    if (name) {
        description = get_quoted_arg(client->buffer, arg_pos, &arg_pos);
        if (description) {
            create_new_channel(server, client, name, description);
            return;
        }
    }
    dprintf(client->fd, "502 Syntax error.\n");
}
