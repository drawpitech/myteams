/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** run_client
*/

#pragma once

#include "client.h"

typedef enum run_state {
    running,
    cli_exit,
    prompt,
} run_state_t;

run_state_t get_serv_info(connection_t *connect);
int get_info_type(connection_t *connect, void *buff, ssize_t size);
