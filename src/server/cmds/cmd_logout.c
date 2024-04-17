/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_logout
*/

#include <myteams/logging_server.h>
#include <string.h>
#include <uuid/uuid.h>

#include "cmds_utils.h"
#include "command.h"
#include "ressources_infos.h"
#include "server.h"

void cmd_logout(server_t *server, client_t *client)
{
    char uuid_str[UUID_STR_LEN] = {0};
    user_info_t info = {0};
    user_t *user = NULL;

    if (uuid_is_null(client->user))
        return;
    user = get_user_by_uuid(server, client->user);
    if (user == NULL)
        return;
    user->status -= 1;
    if (user->status < 0)
        user->status = 0;
    uuid_unparse(user->uuid, uuid_str);
    server_event_user_logged_out(uuid_str);
    broadcast(server, "312", user_to_info(user, &info, NULL), sizeof info);
    uuid_clear(client->user);
}
