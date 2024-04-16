/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_user
*/

#include <string.h>
#include <uuid/uuid.h>

#include "cmds/cmds_utils.h"
#include "command.h"
#include "ressources_infos.h"

static user_t *get_user(server_t *server, client_t *client, uuid_t uuid)
{
    user_t *user = get_user_by_uuid(server, uuid);
    char uuid_str[UUID_STR_LEN] = {0};

    uuid_unparse(uuid, uuid_str);
    if (user != NULL)
        return user;
    write(client->fd, "514", 3);
    write(client->fd, uuid_str, sizeof uuid_str);
    return NULL;
}

void cmd_user(server_t *server, client_t *client)
{
    user_t *user = NULL;
    uuid_t uuid = {0};
    user_info_t info = {0};
    char *arg = NULL;

    if (!is_logged_in(client))
        return;
    arg = get_quoted_arg(client->buffer, 0, NULL);
    if (arg == NULL)
        arg = "";
    uuid_parse(arg, uuid);
    user = get_user(server, client, uuid);
    if (user == NULL)
        return;
    write(client->fd, "215", 3);
    write(client->fd, user_to_info(user, &info), sizeof info);
}
