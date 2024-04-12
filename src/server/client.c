/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** client
*/

#include "client.h"

#include <bits/types.h>
#include <string.h>
#include <sys/select.h>
#include <uuid/uuid.h>

#include "command.h"
#include "debug.h"
#include "server.h"

void client_init(client_t *client, int fd)
{
    if (client == NULL)
        return;
    memset(client, 0, sizeof *client);
    client->fd = fd;
    client->buffer[0] = '\0';
    client->user = NULL;
    DEBUG_MSG("Client connected\n");
}

void client_disconnect(client_t *client)
{
    close(client->fd);
    client->fd = -1;
    DEBUG_MSG("Client disconnected\n");
}

static void client_process_message(
    server_t *serv, client_t *client, char *buffer)
{
    char *ptr = NULL;

    if (client == NULL || buffer == NULL || buffer[0] == '\0')
        return;
    ptr = strchr(buffer, '\n');
    if (ptr == NULL) {
        strcat(client->buffer, buffer);
        return;
    }
    *ptr = '\0';
    strcat(client->buffer, buffer);
    if (client->buffer[0] == '\0')
        return;
    exec_command(serv, client);
    client->buffer[0] = '\0';
    client_process_message(serv, client, ptr + 1);
}

static bool client_wrote(client_t *client)
{
    fd_set fdread;
    struct timeval tv = {.tv_sec = 0, .tv_usec = 1000};

    if (client->fd == -1)
        return false;
    FD_ZERO(&fdread);
    FD_SET(client->fd, &fdread);
    if (select(client->fd + 1, &fdread, NULL, NULL, &tv) <= 0)
        return false;
    return true;
}

void handle_client(server_t *serv, client_t *client)
{
    char buffer[BUFSIZ + 1];
    ssize_t size = 0;

    if (!client_wrote(client))
        return;
    size = read(client->fd, buffer, BUFSIZ);
    if (size == 0 || size == -1) {
        client_disconnect(client);
        return;
    }
    buffer[size] = 0;
    client_process_message(serv, client, buffer);
}
