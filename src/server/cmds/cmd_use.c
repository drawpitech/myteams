/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_use
*/

#include <myteams/logging_server.h>
#include <string.h>
#include <uuid/uuid.h>

#include "cmds_utils.h"
#include "command.h"
#include "debug.h"
#include "server.h"

static void set_team(server_t *server, client_t *client, char **ptr)
{
    size_t end = 0;
    uuid_t uuid = {0};

    *ptr = get_quoted_arg(*ptr, 0, &end);
    if (*ptr == NULL)
        return;
    uuid_parse(*ptr, uuid);
    *ptr += end + 1;
    memcpy(client->uuid.team, uuid, sizeof uuid);
    if (uuid_is_null(client->uuid.team))
        client->uuid.team[0] = 1;
    client->team = get_team_by_uuid(server, uuid);
}

static void set_channel(UNUSED server_t *server, client_t *client, char **ptr)
{
    size_t end = 0;
    uuid_t uuid = {0};

    *ptr = get_quoted_arg(*ptr, 0, &end);
    if (*ptr == NULL)
        return;
    uuid_parse(*ptr, uuid);
    *ptr += end + 1;
    memcpy(client->uuid.channel, uuid, sizeof uuid);
    if (client->team != NULL)
        client->channel = get_channel_by_uuid(client->team, uuid);
}

static void set_thread(UNUSED server_t *server, client_t *client, char **ptr)
{
    size_t end = 0;
    uuid_t uuid = {0};

    *ptr = get_quoted_arg(*ptr, 0, &end);
    if (*ptr == NULL)
        return;
    uuid_parse(*ptr, uuid);
    *ptr += end + 1;
    memcpy(client->uuid.thread, uuid, sizeof uuid);
    if (client->channel != NULL)
        client->thread = get_thread_by_uuid(client->channel, uuid);
}

DEBUG_USED static void debug_cmd_use(client_t *client)
{
    char uuid[UUID_STR_LEN] = {0};

    uuid_unparse(client->uuid.team, uuid);
    DEBUG("Team: (%s) %p", uuid, (void *)client->team);
    uuid_unparse(client->uuid.channel, uuid);
    DEBUG("Channel: (%s) %p", uuid, (void *)client->channel);
    uuid_unparse(client->uuid.thread, uuid);
    DEBUG("Thread: (%s) %p", uuid, (void *)client->thread);
}

void cmd_use(server_t *server, client_t *client)
{
    char *ptr = NULL;

    if (!is_logged_in(client))
        return;
    ptr = client->buffer;
    memset(&client->uuid, 0, sizeof client->uuid);
    client->team = NULL;
    client->channel = NULL;
    client->thread = NULL;
    set_team(server, client, &ptr);
    set_channel(server, client, &ptr);
    set_thread(server, client, &ptr);
    DEBUG_DO(debug_cmd_use(client));
}
