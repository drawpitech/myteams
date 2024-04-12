/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** login
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <uuid/uuid.h>

#include "command.h"
#include "ressources_infos.h"
#include "server.h"
#include "../libs/myteams/logging_server.h"

static void send_info(server_t *server, client_t *client, char *code)
{
    user_info_t info = {0};

    strcpy(info.user_name, client->user->name);
    uuid_copy(info.user_uuid, client->user->uuid);
    for (size_t i = 0; i < server->clients.size; i++) {
        dprintf(server->clients.arr[i].fd, "%s", code);
        write(server->clients.arr[i].fd, &info, sizeof(info));
    }
}

static void create_user(server_t *server, client_t *client, char *name)
{
    user_t new = {0};
    char uuid_str[37] = {0};

    strcpy(new.name, name);
    uuid_generate(new.uuid);
    uuid_unparse(new.uuid, uuid_str);
    append_to_array(&server->users, sizeof(user_t), &new);
    client->user = &server->users.arr[server->users.size - 1];
    server_event_user_created(uuid_str, new.name);
}

static void assign_user(client_t *client, user_t *user)
{
    char uuid_str[37] = {0};

    client->user = user;
    uuid_unparse(user->uuid, uuid_str);
    server_event_user_logged_in(uuid_str);
}

void cmd_login(server_t *server, client_t *client)
{
    int ag = 0;
    char *name = get_arg(client->buffer, 0, &ag);
    user_t *loged = NULL;

    if (!name) {
        dprintf(client->fd, "503 Syntax error.\n");
        return;
    }
    for (size_t i = 0; i < server->users.size; i ++) {
        if (strcmp(name, server->users.arr[i].name) == 0)
            loged = &server->users.arr[i];
    }
    if (loged)
        assign_user(client, loged);
    else
        create_user(server, client, name);
    send_info(server, client, "311");
}

void cmd_logout(server_t *server, client_t *client)
{
    char uuid_str[37] = {0};

    uuid_unparse(client->thread_uuid, uuid_str);
    server_event_user_logged_out(uuid_str);
    send_info(server, client, "312");
    client->user = NULL;
}
