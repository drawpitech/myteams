/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_login
*/

#include <myteams/logging_server.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <uuid/uuid.h>

#include "cmds_utils.h"
#include "command.h"
#include "debug.h"
#include "ressources_infos.h"
#include "server.h"

static void create_user(server_t *server, client_t *client, char *name)
{
    user_t new = {0};
    char uuid_str[37] = {0};

    strcpy(new.name, name);
    uuid_generate(new.uuid);
    uuid_unparse(new.uuid, uuid_str);
    append_to_array(&server->users, sizeof new, &new);
    client->user = &server->users.arr[server->users.size - 1];
    DEBUG("User %s <%s> created", client->user->name, uuid_str);
    server_event_user_created(uuid_str, client->user->name);
}

static void assign_user(client_t *client, user_t *user)
{
    char uuid_str[37] = {0};

    client->user = user;
    uuid_unparse(user->uuid, uuid_str);
    DEBUG("User %s <%s> logged", client->user->name, uuid_str);
    server_event_user_logged_in(uuid_str);
}

static user_t *get_user_by_name(server_t *server, char *name)
{
    for (size_t i = 0; i < server->users.size; i++)
        if (strcmp(name, server->users.arr[i].name) == 0)
            return &server->users.arr[i];
    return NULL;
}

void cmd_login(server_t *server, client_t *client)
{
    size_t ag = 0;
    char *name = get_quoted_arg(client->buffer, 0, &ag);
    user_t *user = NULL;
    user_info_t info = {0};

    if (name == NULL) {
        dprintf(client->fd, "503 Syntax error.\n");
        return;
    }
    user = get_user_by_name(server, name);
    if (user != NULL)
        assign_user(client, user);
    else
        create_user(server, client, name);
    strcpy(info.user_name, client->user->name);
    uuid_copy(info.user_uuid, client->user->uuid);
    broadcast(server, "311", &info, sizeof info);
}
