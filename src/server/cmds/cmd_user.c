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

void cmd_user(server_t *server, client_t *client)
{
    user_t *user = NULL;
    uuid_t uuid;
    user_info_t info;
    char *arg = get_quoted_arg(client->buffer, 0, NULL);

    if (arg == NULL) {
        write(client->fd, "500\n", 4);
        return;
    }
    uuid_parse(arg, uuid);
    user = get_user_by_uuid(server, uuid);
    if (user == NULL) {
        write(client->fd, "500\n", 4);
        return;
    }
    write(client->fd, "200 ", 4);
    write(client->fd, user_to_info(user, &info), sizeof info);
}
