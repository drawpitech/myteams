/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** server
*/

#include <bits/types.h>
#include <string.h>
#include <sys/select.h>

#include "debug.h"
#include "server.h"

static bool client_wrote(client_t *client)
{
    fd_set fdread;
    fd_set fdwrite;
    struct timeval tv = {.tv_sec = 0, .tv_usec = 1000};

    if (client->fd == -1)
        return false;
    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_SET(client->fd, &fdread);
    FD_SET(client->fd, &fdwrite);
    if (select(client->fd + 1, &fdread, &fdwrite, NULL, &tv) <= 0)
        return false;
    return true;
}

static void client_disconnect(client_t *client)
{
    close(client->fd);
    client->fd = -1;
}

static void exec_command(UNUSED server_t *server, client_t *client)
{
    char *buffer = client->buffer;

    printf("buffer: `%s`\n", buffer);
    dprintf(client->fd, "PONG\n");
}

static void client_process_message(
    server_t *serv, client_t *client, char *buffer)
{
    char *ptr = NULL;

    if (client == NULL || buffer == NULL || buffer[0] == '\0')
        return;
    DEBUG("client said: %s", buffer);
    ptr = strchr(buffer, '\n');
    if (ptr == NULL) {
        strcat(client->buffer, buffer);
        return;
    }
    *ptr = '\0';
    if (buffer[0] != '\0' && *(ptr - 1) == '\r')
        *(ptr - 1) = '\0';
    strcat(client->buffer, buffer);
    DEBUG("buf: %s\n", client->buffer);
    exec_command(serv, client);
    client->buffer[0] = '\0';
    client_process_message(serv, client, ptr + 1);
}

void handle_client(server_t *serv, client_t *client)
{
    char buffer[BUFSIZ + 1];
    ssize_t size = 0;
    fd_set fdread;
    struct timeval tv = {.tv_sec = 0, .tv_usec = 1000};

    if (!client_wrote(client))
        return;
    if (client == NULL)
        return;
    FD_ZERO(&fdread);
    FD_SET(client->fd, &fdread);
    if (select(client->fd + 1, &fdread, NULL, NULL, &tv) <= 0)
        return;
    size = read(client->fd, buffer, BUFSIZ);
    if (size == 0 || size == -1) {
        client_disconnect(client);
        return;
    }
    buffer[size] = 0;
    client_process_message(serv, client, buffer);
}
