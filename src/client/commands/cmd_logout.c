/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_logout
*/

#include <stdio.h>
#include <string.h>

#include "client.h"
#include "command.h"
#include "utils.h"

int cmd_logout(
    connection_t *connect, const char *cmd, const cmd_conv_t *command)
{
    connect->last_cmd = other;
    dprintf(
        connect->servfd, "%s%s\n", command->conv, cmd + strlen(command->cmd));
    return SUCCESS;
}
