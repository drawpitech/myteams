/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** serve_info
*/

#include "client.h"
#include "run_client.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>

static int display_received(connection_t *connect)
{
    char buff[BUFSIZ];

    if (read(connect->servfd, buff, BUFSIZ) > 0)
        printf("%s\n", buff);

    return SUCCESS;
}

run_state_t get_serv_info(connection_t *connect)
{
    if (display_received(connect))
        dprintf(STDERR_FILENO, "Error while displaying server info\n");

    printf("> ");
    fflush(stdout);
    return running;
}
