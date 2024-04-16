/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_create
*/

#include <myteams/logging_client.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <uuid/uuid.h>

#include "client.h"
#include "command.h"
#include "utils.h"

int cmd_create(
    connection_t *connect, const char *cmd, const cmd_conv_t *command)
{
    connect->last_cmd = create;
    dprintf(
        connect->servfd, "%s%s\n", command->conv, cmd + strlen(command->cmd));
    return SUCCESS;
}
