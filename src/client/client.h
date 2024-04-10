/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** client
*/

#pragma once

#include <netinet/in.h>

typedef struct connection_s {
    int servfd;
    struct sockaddr_in sockaddr;
} connection_t;

int myteams_cli(int argc, char **argv);
int run_client(connection_t *connection);
