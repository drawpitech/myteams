/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** reply_single
*/

#include <myteams/logging_client.h>
#include <uuid/uuid.h>

#include "client.h"
#include "handle_event.h"
#include "ressources_infos.h"
#include "run_client.h"
#include "utils.h"

int reply_s_team(connection_t *connect)
{
    team_info_t info = {0};
    char uuid_str[UUID_STR_LEN] = {0};

    connect->wait -= 1;
    if (get_info_type(connect, &info, sizeof(info)) != SUCCESS)
        return ERROR;
    uuid_unparse(info.uuid, uuid_str);
    if (connect->last_cmd == create)
        client_print_team_created(uuid_str, info.name, info.description);
    else
        client_print_team(uuid_str, info.name, info.description);
    return SUCCESS;
}

int reply_s_channel(connection_t *connect)
{
    channel_info_t info = {0};
    char uuid_str[UUID_STR_LEN] = {0};

    connect->wait -= 1;
    if (get_info_type(connect, &info, sizeof(info)) != SUCCESS)
        return ERROR;
    uuid_unparse(info.uuid, uuid_str);
    if (connect->last_cmd == create)
        client_print_channel_created(uuid_str, info.name, info.description);
    else
        client_print_channel(uuid_str, info.name, info.description);
    return SUCCESS;
}

int reply_s_thread(connection_t *connect)
{
    thread_info_t info = {0};
    char uuid_str[UUID_STR_LEN] = {0};
    char user_uuid_str[UUID_STR_LEN] = {0};

    connect->wait -= 1;
    if (get_info_type(connect, &info, sizeof(info)) != SUCCESS)
        return ERROR;
    uuid_unparse(info.thread_uuid, uuid_str);
    uuid_unparse(info.user_uuid, user_uuid_str);
    if (connect->last_cmd == create)
        client_print_thread_created(
            uuid_str, user_uuid_str, info.timestamp, info.title, info.body);
    else
        client_print_thread(
            uuid_str, user_uuid_str, info.timestamp, info.title, info.body);
    return SUCCESS;
}

int reply_s_reply(connection_t *connect)
{
    reply_info_t info = {0};
    char thread_uuid[UUID_STR_LEN] = {0};
    char user_uuid[UUID_STR_LEN] = {0};

    connect->wait -= 1;
    if (get_info_type(connect, &info, sizeof(info)) != SUCCESS)
        return ERROR;
    uuid_unparse(info.thread_uuid, thread_uuid);
    uuid_unparse(info.user_uuid, user_uuid);
    if (connect->last_cmd == create)
        client_print_reply_created(
            thread_uuid, user_uuid, info.timestamp, info.body);
    return SUCCESS;
}
