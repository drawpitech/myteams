/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** handle_erros
*/

#include <myteams/logging_client.h>
#include <unistd.h>
#include <uuid/uuid.h>

#include "client.h"
#include "handle_event.h"
#include "utils.h"

int standard_error(connection_t *connect)
{
    char c = '\0';

    connect->wait -= 1;
    while (c != '\n') {
        if (read(connect->servfd, &c, 1) == 1)
            write(1, &c, 1);
    }
    return SUCCESS;
}

int error_unauthorized(UNUSED connection_t *connect)
{
    connect->wait -= 1;
    client_error_unauthorized();
    return SUCCESS;
}

int error_already_exist(UNUSED connection_t *connect)
{
    connect->wait -= 1;
    client_error_already_exist();
    return SUCCESS;
}
