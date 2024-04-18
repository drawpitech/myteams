/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** save
*/

#pragma once

#include "server.h"

#define FILE_EXTENSION ".tits"
#define DATA_FILE      "data"FILE_EXTENSION

void save_server(server_t *server);
void load_server(server_t *server);
