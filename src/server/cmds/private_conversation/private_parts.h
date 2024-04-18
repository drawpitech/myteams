/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** private_parts
*/

#pragma once

#include "server.h"
#include <uuid/uuid.h>

discussion_t *get_discussion(
    server_t *server, uuid_t uuid1, uuid_t uuid2);
bool user_exist(
    server_t *server, client_t *client, uuid_t uuid, char *uuid_str);
bool get_uuid(
    server_t *server, client_t *client, uuid_t *uuid, size_t *arg_pos);
