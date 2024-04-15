/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmds_utils
*/

#pragma once

#include "ressources_infos.h"
#include "server.h"

void broadcast(server_t *server, char *code, void *msg, size_t size);
char *get_quoted_arg(char *buff, size_t start, size_t *end);
bool is_logged_in(client_t *client);
user_info_t *user_to_info(user_t *user, user_info_t *info);
