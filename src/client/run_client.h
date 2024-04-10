/*
** EPITECH PROJECT, 2024
** teams
** File description:
** run_client
*/

#pragma once

#include "client.h"

typedef enum run_state {
    running,
    cli_exit,
} run_state_t;

run_state_t get_serv_info(connection_t *connect);
