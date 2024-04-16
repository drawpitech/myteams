/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_help
*/

#include <stdio.h>

#include "client.h"
#include "command.h"
#include "utils.h"

int cmd_help(
    connection_t *connect, UNUSED const char *cmd,
    UNUSED const cmd_conv_t *command)
{
    connect->last_cmd = other;
    for (size_t i = 0; i < LEN_OF(commands); i++)
        printf("%s: %s\n", commands[i].cmd, commands[i].help);
    return SUCCESS;
}
