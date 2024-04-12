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

int get_info_type(connection_t *connect, void *buff, ssize_t size)
{
    if (read(connect->servfd, buff, size) < size) {
        dprintf(STDERR_FILENO, "Error: read from server failed.\n");
        return ERROR;
    }
    return SUCCESS;
}

run_state_t get_serv_info(connection_t *connect)
{
    char code[3] = "000";

    if (get_info_type(connect, code, sizeof(code)) != SUCCESS) {
        dprintf(STDERR_FILENO, "Error: didn't manage to read from server.\n");
        return running;
    }
    if (code[0] != 3) {
        dprintf(STDOUT_FILENO, "Error: code %s should not be here.", code);
        return cli_exit;
    }
    return running;
}
