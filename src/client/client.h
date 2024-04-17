/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** client
*/

#pragma once

#include <netinet/in.h>

enum command_type {
    create,
    subscribe,
    unsubscribe,
    info_cmd,
    other,
};

typedef struct connection_s {
    int servfd;
    struct sockaddr_in sockaddr;
    enum command_type last_cmd;
} connection_t;

int myteams_cli(int argc, char **argv);
int run_client(connection_t *connection);
