/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** reply_list
*/

#include <myteams/logging_client.h>
#include <unistd.h>
#include <uuid/uuid.h>

#include "client.h"
#include "handle_event.h"
#include "ressources_infos.h"
#include "run_client.h"
#include "utils.h"

int standar_success(connection_t *connect)
{
    char c = '\0';

    while (c != '\n') {
        if (read(connect->servfd, &c, 1) == 1)
            write(1, &c, 1);
    }
    return SUCCESS;
}

int reply_l_team(connection_t *connect)
{
    team_info_t info = {0};
    size_t nb_elt = 0;
    char uuid_str[UUID_STR_LEN] = {0};

    if (get_info_type(connect, &nb_elt, sizeof(nb_elt)) != SUCCESS)
        return ERROR;
    for (size_t i = 0; i < nb_elt; i++) {
        if (get_info_type(connect, &info, sizeof(info)) != SUCCESS)
            return ERROR;
        uuid_unparse(info.uuid, uuid_str);
        client_print_teams(uuid_str, info.name, info.description);
    }
    return SUCCESS;
}

int reply_l_channel(connection_t *connect)
{
    channel_info_t info = {0};
    size_t nb_elt = 0;
    char uuid_str[UUID_STR_LEN] = {0};

    if (get_info_type(connect, &nb_elt, sizeof(nb_elt)) != SUCCESS)
        return ERROR;
    for (size_t i = 0; i < nb_elt; i++) {
        if (get_info_type(connect, &info, sizeof(info)) != SUCCESS)
            return ERROR;
        uuid_unparse(info.uuid, uuid_str);
        client_team_print_channels(uuid_str, info.name, info.description);
    }
    return SUCCESS;
}

int reply_l_threads(connection_t *connect)
{
    thread_info_t info = {0};
    size_t nb_elt = 0;
    char user_uuid[UUID_STR_LEN] = {0};
    char thread_uuid[UUID_STR_LEN] = {0};

    if (get_info_type(connect, &nb_elt, sizeof(nb_elt)) != SUCCESS)
        return ERROR;
    for (size_t i = 0; i < nb_elt; i++) {
        if (get_info_type(connect, &info, sizeof(info)) != SUCCESS)
            return ERROR;
        uuid_unparse(info.user_uuid, user_uuid);
        uuid_unparse(info.thread_uuid, thread_uuid);
        client_channel_print_threads(
            thread_uuid, user_uuid, info.timestamp, info.title, info.body);
    }
    return SUCCESS;
}

int reply_l_replies(connection_t *connect)
{
    reply_info_t info = {0};
    size_t nb_elt = 0;
    char user_uuid[UUID_STR_LEN] = {0};
    char thread_uuid[UUID_STR_LEN] = {0};

    if (get_info_type(connect, &nb_elt, sizeof(nb_elt)) != SUCCESS)
        return ERROR;
    for (size_t i = 0; i < nb_elt; i++) {
        if (get_info_type(connect, &info, sizeof(info)) != SUCCESS)
            return ERROR;
        uuid_unparse(info.user_uuid, user_uuid);
        uuid_unparse(info.thread_uuid, thread_uuid);
        client_thread_print_replies(
            thread_uuid, user_uuid, info.timestamp, info.body);
    }
    return SUCCESS;
}
