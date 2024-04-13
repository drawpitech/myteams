/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** serve_info
*/

#include "client.h"
#include "event_handling/handle_event.h"
#include "run_client.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int get_info_type(connection_t *connect, void *buff, ssize_t size)
{
    if (read(connect->servfd, buff, size) < size) {
        dprintf(STDERR_FILENO, "Error: read from server failed.\n");
        return ERROR;
    }
    return SUCCESS;
}

static void display_error(connection_t *connect)
{
    char c = '\0';

    while (c != '\n') {
        if (read(connect->servfd, &c, 1) == 1)
            write(1, &c, 1);
    }
}

run_state_t get_serv_info(connection_t *connect)
{
    char code[4] = "000\0";
    int res = -1;

    if (get_info_type(connect, code, 3) != SUCCESS) {
        dprintf(STDERR_FILENO, "Error: didn't manage to read from server.\n");
        return cli_exit;
    }
    for (size_t i = 0; i < LEN_OF(func_code_tab); i++) {
        if (strncmp(func_code_tab[i].code, code, 3) == 0){
            res = func_code_tab[i].func(connect);
            break;
        }
    }
    if (res == -1) {
        display_error(connect);
        return running;
    }
    return running;
}
