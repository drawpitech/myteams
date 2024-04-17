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

static void parse_uuid(char **ptr, uuid_t *target)
{
    size_t end = 0;
    uuid_t uuid = {0};

    uuid_clear(*target);
    *ptr = get_quoted_arg(*ptr, 0, &end);
    if (*ptr == NULL)
        return;
    uuid_parse(*ptr, uuid);
    *ptr += end + 1;
    uuid_copy(*target, uuid);
    if (uuid_is_null(*target))
        uuid_copy(*target, INVALID_UUID);
}

DEBUG_USED static void debug_cmd_use(client_t *client)
{
    char uuid[UUID_STR_LEN] = {0};

    uuid_unparse(client->team, uuid);
    DEBUG("Team: (%s) %p", uuid, (void *)client->team);
    uuid_unparse(client->channel, uuid);
    DEBUG("Channel: (%s) %p", uuid, (void *)client->channel);
    uuid_unparse(client->thread, uuid);
    DEBUG("Thread: (%s) %p", uuid, (void *)client->thread);
}

void cmd_use(UNUSED server_t *server, client_t *client)
{
    char *ptr = NULL;

    if (!is_logged_in(client))
        return;
    ptr = client->buffer;
    parse_uuid(&ptr, &client->team);
    parse_uuid(&ptr, &client->channel);
    parse_uuid(&ptr, &client->thread);
    DEBUG_DO(debug_cmd_use(client));
}
