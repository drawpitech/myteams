/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** serve_info
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "client.h"
#include "event_handling/handle_event.h"
#include "run_client.h"
#include "utils.h"

int get_info_type(connection_t *connect, void *buff, ssize_t size)
{
    if (read(connect->servfd, buff, size) < size) {
        dprintf(STDOUT_FILENO, "Error: read from server failed.\n");
        return ERROR;
    }
    return SUCCESS;
}

run_state_t get_serv_info(connection_t *connect)
{
    char code[4] = "000\0";

    if (get_info_type(connect, code, 3) != SUCCESS)
        return cli_exit;
    for (size_t i = 0; i < LEN_OF(func_code_tab); i++) {
        if (strncmp(func_code_tab[i].code, code, 3) == 0)
            return func_code_tab[i].func(connect)
                == SUCCESS ? running : cli_exit;
    }
    dprintf(STDOUT_FILENO, "Error: wrong reply received from server\n");
    return cli_exit;
}
