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
#include "ressources_infos.h"
#include "utils.h"

static int team_created(connection_t *connect)
{
    team_info_t info = {0};
    char uuid_str[37] = {0};

    if (read(connect->servfd, &info, sizeof(info)) != sizeof(info))
        return ERROR;
    uuid_unparse(info.uuid, uuid_str);
    client_print_team_created(uuid_str, info.name, info.description);
    return SUCCESS;
}

static int channel_created(connection_t *connect)
{
    channel_info_t info = {0};
    char uuid_str[37] = {0};

    if (read(connect->servfd, &info, sizeof(info)) != sizeof(info))
        return ERROR;
    uuid_unparse(info.uuid, uuid_str);
    client_print_channel_created(uuid_str, info.name, info.description);
    return SUCCESS;
}

static int thread_created(connection_t *connect)
{
    thread_info_t info = {0};
    char uuid_str[37] = {0};
    char user_uuid_str[37] = {0};

    if (read(connect->servfd, &info, sizeof(info)) != sizeof(info))
        return ERROR;
    uuid_unparse(info.thread_uuid, uuid_str);
    uuid_unparse(info.user_uuid, user_uuid_str);
    client_print_thread_created(
        uuid_str, user_uuid_str, info.timestamp, info.title, info.body);
    return SUCCESS;
}

static int reply_created(connection_t *connect)
{
    reply_info_t info = {0};
    char thread_uuid[37] = {0};
    char user_uuid[37] = {0};

    if (read(connect->servfd, &info, sizeof(info)) != sizeof(info))
        return ERROR;
    uuid_unparse(info.thread_uuid, thread_uuid);
    uuid_unparse(info.user_uuid, user_uuid);
    client_print_reply_created(
        thread_uuid, user_uuid, info.timestamp, info.body);
    return SUCCESS;
}

static int select_function(connection_t *connect, char type)
{
    switch (type) {
        case '1':
            return team_created(connect);
        case '2':
            return channel_created(connect);
        case '3':
            return thread_created(connect);
        case '4':
            return reply_created(connect);
        default:
            return SUCCESS;
    }
}

int cmd_create(
    connection_t *connect, const char *cmd, const cmd_conv_t *command)
{
    char code[4] = {0};

    dprintf(
        connect->servfd, "%s%s\n", command->conv, cmd + strlen(command->cmd));
    if (read(connect->servfd, code, sizeof(code)) != sizeof(code))
        return ERROR;
    if (code[0] != '2' && code[1] != '1')
        return SUCCESS;
    return select_function(connect, code[2]);
}
