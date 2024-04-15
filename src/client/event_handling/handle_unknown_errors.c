/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** handle_unknown_errors
*/

#include <myteams/logging_client.h>
#include <unistd.h>
#include <uuid/uuid.h>

#include "client.h"
#include "handle_event.h"
#include "ressources_infos.h"
#include "run_client.h"
#include "utils.h"

int unknown_team(connection_t *connect)
{
    char uuid[37] = {0};

    if (get_info_type(connect, &uuid, sizeof(uuid)) != SUCCESS)
        return ERROR;
    client_error_unknown_team(uuid);
    return SUCCESS;
}

int unknown_channel(connection_t *connect)
{
    char uuid[37] = {0};

    if (get_info_type(connect, &uuid, sizeof(uuid)) != SUCCESS)
        return ERROR;
    client_error_unknown_channel(uuid);
    return SUCCESS;
}

int unknown_thread(connection_t *connect)
{
    char uuid[37] = {0};

    if (get_info_type(connect, &uuid, sizeof(uuid)) != SUCCESS)
        return ERROR;
    client_error_unknown_thread(uuid);
    return SUCCESS;
}

int unknown_user(connection_t *connect)
{
    char uuid[37] = {0};

    if (get_info_type(connect, &uuid, sizeof(uuid)) != SUCCESS)
        return ERROR;
    client_error_unknown_user(uuid);
    return SUCCESS;
}
