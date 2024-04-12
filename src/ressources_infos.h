/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** ressources_infos
*/

#pragma once

#include <time.h>

typedef struct team_info {
    char *team_uuid;
    char *team_name;
    char *team_description;
} team_info_t;

typedef struct channel_info {
    char *channel_uuid;
    char *channel_name;
    char *channel_description;
} channel_info_t;

typedef struct thread_info {
    char *thread_uuid;
    char *user_uuid;
    time_t thread_timestamp;
    char *thread_title;
    char *thread_body;
} thread_info_t;

typedef struct reply_info {
    char *thread_uuid;
    char *user_uuid;
    time_t reply_timestamp;
    char *reply_body;
} reply_info_t;

typedef struct message_info {
    char *sender_uuid;
    time_t message_timestamp;
    char *message_body;
} message_info_t;

typedef struct user_info {
    char *user_uuid;
    char *user_name;
    int user_status;
} user_info_t;
