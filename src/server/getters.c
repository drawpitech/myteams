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
    user_t *user = NULL;

    for (size_t i = 0; i < server->clients.size; i++) {
        user = server->clients.arr[i].user;
        if (user != NULL && memcmp(user->uuid, uuid, sizeof(uuid_t)) == 0)
            return user;
    }
    return NULL;
}
