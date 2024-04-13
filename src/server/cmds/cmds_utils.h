/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmds_utils
*/

#pragma once

#include "server.h"

void broadcast(server_t *server, char *code, void *msg, size_t size);
char *get_quoted_arg(char *buff, size_t start, size_t *end);
