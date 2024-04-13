/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** handle_event
*/

#include "handle_event.h"

#include <myteams/logging_client.h>
#include <uuid/uuid.h>

#include "client.h"
#include "ressources_infos.h"
#include "run_client.h"
#include "utils.h"

int receive_login(connection_t *connect)
{
    user_info_t user_info = {0};
    char uuid_str[37] = {0};

    if (get_info_type(connect, &user_info, sizeof(user_info)) != SUCCESS)
        return ERROR;
    uuid_unparse(user_info.user_uuid, uuid_str);
    client_event_logged_in(uuid_str, user_info.user_name);
    return SUCCESS;
}

int receive_logout(connection_t *connect)
{
    user_info_t user_info = {0};
    char uuid_str[37] = {0};

    if (get_info_type(connect, &user_info, sizeof(user_info)) != SUCCESS)
        return ERROR;
    uuid_unparse(user_info.user_uuid, uuid_str);
    client_event_logged_out(uuid_str, user_info.user_name);
    return SUCCESS;
}

int receive_message(connection_t *connect)
{
    message_info_t message_info = {0};
    char uuid_str[37] = {0};

    if (get_info_type(connect, &message_info, sizeof(message_info)) != SUCCESS)
        return ERROR;
    uuid_unparse(message_info.sender_uuid, uuid_str);
    client_event_private_message_received(uuid_str, message_info.message_body);
    return SUCCESS;
}

int receive_reply(connection_t *connect)
{
    reply_info_t reply_info = {0};
    char team_uuid_str[37] = {0};
    char thread_uuid_str[37] = {0};
    char user_uuid_str[37] = {0};

    if (get_info_type(connect, &reply_info, sizeof(reply_info)) != SUCCESS)
        return ERROR;
    uuid_unparse(reply_info.thread_uuid, thread_uuid_str);
    uuid_unparse(reply_info.user_uuid, user_uuid_str);
    uuid_unparse(reply_info.team_uuid, team_uuid_str);
    client_event_thread_reply_received(
        team_uuid_str, thread_uuid_str, user_uuid_str, reply_info.reply_body);
    return SUCCESS;
}
