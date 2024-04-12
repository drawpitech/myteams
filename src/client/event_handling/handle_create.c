/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** handle_create
*/

#include "handle_event.h"

#include <uuid/uuid.h>

#include "../libs/myteams/logging_client.h"
#include "client.h"
#include "ressources_infos.h"
#include "run_client.h"
#include "utils.h"

int receive_created_teams(connection_t *connect)
{
    team_info_t team_info = {0};
    char uuid_str[37] = {0};

    if (get_info_type(connect, &team_info, sizeof(team_info)) != SUCCESS)
        return ERROR;
    uuid_unparse(team_info.team_uuid, uuid_str);
    client_event_team_created(
        uuid_str, team_info.team_name, team_info.team_description);
    return SUCCESS;
}

int receive_created_channel(connection_t *connect)
{
    channel_info_t channel_info = {0};
    char uuid_str[37] = {0};

    if (get_info_type(connect, &channel_info, sizeof(channel_info)) != SUCCESS)
        return ERROR;
    uuid_unparse(channel_info.channel_uuid, uuid_str);
    client_event_channel_created(
        uuid_str, channel_info.channel_name, channel_info.channel_description);
    return SUCCESS;
}

int receive_created_thread(connection_t *connect)
{
    thread_info_t thread_info = {0};
    char user_uuid_str[37] = {0};
    char thread_uuid_str[37] = {0};

    if (get_info_type(connect, &thread_info, sizeof(thread_info)) != SUCCESS)
        return ERROR;
    uuid_unparse(thread_info.user_uuid, user_uuid_str);
    uuid_unparse(thread_info.thread_uuid, thread_uuid_str);
    client_event_thread_created(
        thread_uuid_str, user_uuid_str, thread_info.thread_timestamp,
        thread_info.thread_title, thread_info.thread_body);
    return SUCCESS;
}
