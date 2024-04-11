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
    if (buffer == NULL || msg == NULL || msg->name == NULL)
        return 1;
    return strncmp(buffer, msg->name, strlen(msg->name));
}

void exec_command(UNUSED server_t *server, client_t *client)
{
    struct cmd_s *c = NULL;
    char cmd[256] = {0};
    char *ptr = cmd;

    strncpy(cmd, client->buffer, sizeof cmd);
    DEBUG("buf: %s", client->buffer);
    for (; *ptr && *ptr != ' '; ptr++);
    *ptr = '\0';
    c = bsearch(
        cmd, COMMANDS, LEN_OF(COMMANDS), sizeof *COMMANDS,
        (int (*)(const void *, const void *))compare);
    if (c == NULL)
        dprintf(client->fd, "wtf is this command\n");
    else
        dprintf(client->fd, "%s: PONG\n", c->name);
}
