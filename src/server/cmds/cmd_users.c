/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_users
*/

/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_list
*/

#include <myteams/logging_client.h>
#include <myteams/logging_server.h>
#include <stdio.h>
#include <unistd.h>
#include <uuid/uuid.h>

#include "cmds/cmds_utils.h"
#include "command.h"
#include "ressources_infos.h"
#include "server.h"

void cmd_users(server_t *server, client_t *client)
{
    user_info_t info = {0};

    if (!server || !client || !is_logged_in(client))
        return;
    dprintf(client->fd, "225");
    fsync(client->fd);
    write(client->fd, &server->users.size, sizeof(server->users.size));
    for (size_t i = 0; i < server->users.size; i++) {
        write(
            client->fd,
            user_to_info(&server->users.arr[i], &info, NULL),
            sizeof(info));
    }
}
