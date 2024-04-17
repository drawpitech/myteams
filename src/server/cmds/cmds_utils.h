/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** cmds_utils
*/

#pragma once

#include <uuid/uuid.h>
#include "ressources_infos.h"
#include "server.h"

bool user_in_team(uuid_t uuid, team_t *team);
void broadcast(server_t *server, char *code, void *msg, size_t size);
char *get_quoted_arg(char *buff, size_t start, size_t *end);
bool is_logged_in(client_t *client);
bool check_context(client_t *client);
user_info_t *user_to_info(user_t *user, user_info_t *info, team_t *team);
team_info_t *team_to_info(team_t *team, team_info_t *info);
channel_info_t *channel_to_info(channel_t *channel, channel_info_t *info);
thread_info_t *thread_to_info(thread_t *thread, thread_info_t *info);
reply_info_t *comment_to_info(
    comment_t *reply, reply_info_t *info, thread_t *thread, team_t *team);
