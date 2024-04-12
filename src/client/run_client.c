/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** run_client
*/

#include "run_client.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "client.h"
#include "commands/command.h"
#include "utils.h"

static run_state_t exec_cmd(
    connection_t *connect, char *cmd, const cmd_conv_t *send)
{
    if (send->func(connect, cmd, send) != SUCCESS)
        return cli_exit;
    return running;
}

static run_state_t handle_cmd(connection_t *connect, char *cmd)
{
    run_state_t state = running;
    size_t i = 0;

    if (!cmd)
        return cli_exit;
    for (; i < LEN_OF(commands); i++) {
        if (strncmp(commands[i].cmd, cmd, strlen(commands[i].cmd)) == 0 &&
            (cmd[strlen(commands[i].cmd)] == ' ' ||
                cmd[strlen(commands[i].cmd)] == '\n')) {
            state = exec_cmd(connect, cmd, &commands[i]);
            break;
        }
    }
    free(cmd);
    if (i == LEN_OF(commands))
        printf("Command not found\n");
    return state;
}

static char *get_command(void)
{
    char *cmd = NULL;
    size_t len = 0;

    if (getline(&cmd, &len, stdin) == -1) {
        free(cmd);
        return NULL;
    }
    return cmd;
}

static bool is_fd_ready(int fd)
{
    struct timeval tv;
    fd_set rfds;

    tv.tv_sec = 1;
    tv.tv_usec = 0;
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);
    if (select(fd + 1, &rfds, NULL, NULL, &tv) > 0)
        return true;
    return false;
}

int run_client(connection_t *connection)
{
    run_state_t state = running;

    if (!connection)
        return MSG_ERR("Memory failed\n");
    while (state != cli_exit) {
        if (state != prompt) {
            printf("> ");
            fflush(stdout);
            state = prompt;
        }
        if (is_fd_ready(STDIN_FILENO))
            state = handle_cmd(connection, get_command());
        if (is_fd_ready(connection->servfd))
            state = get_serv_info(connection);
    }
    close(connection->servfd);
    return SUCCESS;
}
