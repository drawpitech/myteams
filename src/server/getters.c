/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** getters
*/

#include <string.h>

#include "server.h"

user_t *get_user_by_uuid(server_t *server, uuid_t uuid)
{
    for (size_t i = 0; i < server->clients.size; i++)
        if (!memcmp(server->clients.arr[i].user.uuid, uuid, sizeof(uuid_t)))
            return &server->clients.arr[i].user;
    return NULL;
}
