/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** client
*/

#pragma once

#include "server.h"

void handle_client(server_t *serv, client_t *client);
void client_init(client_t *client, int fd);
void client_disconnect(client_t *client);
