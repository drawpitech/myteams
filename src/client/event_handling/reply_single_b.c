/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** reply_single_b
*/

#include <myteams/logging_client.h>
#include <uuid/uuid.h>

#include "client.h"
#include "handle_event.h"
#include "ressources_infos.h"
#include "run_client.h"
#include "utils.h"

int reply_s_user(connection_t *connect)
{
    user_info_t info = {0};
    char user_uuid[UUID_STR_LEN] = {0};
    char team_uuid[UUID_STR_LEN] = {0};

    if (get_info_type(connect, &info, sizeof(info)) != SUCCESS)
        return ERROR;
    uuid_unparse(info.user_uuid, user_uuid);
    uuid_unparse(info.team_uuid, team_uuid);
    if (connect->last_cmd == subscribe)
        client_print_subscribed(user_uuid, team_uuid);
    if (connect->last_cmd == unsubscribe)
        client_print_unsubscribed(user_uuid, team_uuid);
    if (connect->last_cmd == info_cmd || connect->last_cmd == other)
        client_print_user(user_uuid, info.name, info.status);
    return SUCCESS;
}

int reply_s_message(connection_t *connect)
{
    user_info_t info = {0};
    char user_uuid[UUID_STR_LEN] = {0};

    if (get_info_type(connect, &info, sizeof(info)) != SUCCESS)
        return ERROR;
    uuid_unparse(info.user_uuid, user_uuid);
    return SUCCESS;
}
