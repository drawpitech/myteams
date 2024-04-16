/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** reply_list_b
*/

#include <myteams/logging_client.h>
#include <unistd.h>
#include <uuid/uuid.h>

#include "client.h"
#include "handle_event.h"
#include "ressources_infos.h"
#include "run_client.h"
#include "utils.h"

int reply_l_users(connection_t *connect)
{
    user_info_t info = {0};
    size_t nb_elt = 0;
    char user_uuid[UUID_STR_LEN] = {0};

    if (get_info_type(connect, &nb_elt, sizeof(nb_elt)) != SUCCESS)
        return ERROR;
    for (size_t i = 0; i < nb_elt; i++) {
        if (get_info_type(connect, &info, sizeof(info)) != SUCCESS)
            return ERROR;
        uuid_unparse(info.user_uuid, user_uuid);
        client_print_users(user_uuid, info.name, info.status);
    }
    return SUCCESS;
}

int reply_l_messages(connection_t *connect)
{
    message_info_t info = {0};
    size_t nb_elt = 0;
    char sender_uuid[UUID_STR_LEN] = {0};

    if (get_info_type(connect, &nb_elt, sizeof(nb_elt)) != SUCCESS)
        return ERROR;
    for (size_t i = 0; i < nb_elt; i++) {
        if (get_info_type(connect, &info, sizeof(info)) != SUCCESS)
            return ERROR;
        uuid_unparse(info.sender_uuid, sender_uuid);
        client_private_message_print_messages(
            sender_uuid, info.timestamp, info.body);
    }
    return SUCCESS;
}
