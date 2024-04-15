/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmd_user
*/

#include <myteams/logging_client.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "client.h"
#include "command.h"
#include "debug.h"
#include "ressources_infos.h"
#include "utils.h"

int cmd_user(connection_t *connect, const char *cmd, const cmd_conv_t *command)
{
    user_info_t info = {0};
    char code[4] = {0};
    char uuid[37] = {0};

    dprintf(
        connect->servfd, "%s%s\n", command->conv, cmd + strlen(command->cmd));
    if (read(connect->servfd, code, sizeof code) != sizeof code)
        return ERROR;
    DEBUG("/user ret: %.3s", code);
    if (strncmp(code, "200", 3) != 0) {
        printf("Server returned: %.3s\n", code);
        return SUCCESS;
    }
    if (read(connect->servfd, &info, sizeof info) != sizeof info)
        return ERROR;
    uuid_unparse(info.user_uuid, uuid);
    client_print_user(uuid, info.user_name, 0);
    return SUCCESS;
}
