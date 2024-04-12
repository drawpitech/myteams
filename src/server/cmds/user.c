/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** user
*/

#include <string.h>
#include <uuid/uuid.h>

#include "command.h"

void cmd_user(server_t *server, client_t *client)
{
    char uuid_str[37];
    user_t *user = NULL;
    uuid_t uuid;

    if (strlen(client->buffer) != 36) {
        dprintf(client->fd, "500\n");
        return;
    }
    uuid_parse(client->buffer, uuid);
    user = get_user_by_uuid(server, uuid);
    uuid_unparse(uuid, uuid_str);
    if (user == NULL) {
        dprintf(client->fd, "500\n");
        return;
    }
    dprintf(client->fd, "200 <%s> \"%s\"\n", uuid_str, user->name);
}
