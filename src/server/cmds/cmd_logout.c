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
    char uuid_str[37] = {0};
    user_info_t info = {0};

    if (client->user == NULL)
        return;
    uuid_unparse(client->user->uuid, uuid_str);
    server_event_user_logged_out(uuid_str);
    strcpy(info.name, client->user->name);
    uuid_copy(info.user_uuid, client->user->uuid);
    broadcast(server, "312", &info, sizeof info);
    client->user = NULL;
}
