/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** command
*/

#include "command.h"

#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "server.h"
#include "utils.h"

static int compare(const char *buffer, const struct cmd_s *msg)
{
    return (msg->name == NULL) ? 1 : strcmp(buffer, msg->name);
}

void exec_command(UNUSED server_t *server, client_t *client)
{
    struct cmd_s *c = NULL;
    char *ptr = client->buffer;

    for (; *ptr; ++ptr) {
        if (*ptr == ' ') {
            *ptr = '\0';
            ++ptr;
            break;
        }
    }
    DEBUG("cmd: `%s`, args: `%s`", client->buffer, ptr);
    c = bsearch(client->buffer, COMMANDS, LEN_OF(COMMANDS), sizeof *COMMANDS,
        (int (*)(const void *, const void *))compare);
    memmove(client->buffer, ptr, strlen(ptr) + 1);
    if (c == NULL)
        dprintf(client->fd, "501 unrecognised command\n");
    else if (c->func == NULL)
        dprintf(client->fd, "503 command not implemented\n");
    else
        c->func(server, client);
}
