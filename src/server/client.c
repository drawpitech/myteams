/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** server
*/

#include <bits/types.h>
#include <sys/select.h>

#include "server.h"

static bool client_wrote(client_t *client)
{
    fd_set fdread;
    fd_set fdwrite;
    struct timeval tv = {.tv_sec = 0, .tv_usec = 1000};

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_SET(client->fd, &fdread);
    FD_SET(client->fd, &fdwrite);
    if (select(client->fd + 1, &fdread, &fdwrite, NULL, &tv) <= 0)
        return false;
    return true;
}

void handle_client(UNUSED server_t *serv, client_t *client)
{
    if (!client_wrote(client))
        return;
}
