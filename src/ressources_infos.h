/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** ressources_infos
*/

#pragma once

#include "utils.h"
#include <time.h>
#include <uuid/uuid.h>

typedef struct team_info {
    uuid_t uuid;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
} team_info_t;

typedef struct channel_info {
    uuid_t uuid;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
} channel_info_t;

typedef struct thread_info {
    uuid_t thread_uuid;
    uuid_t user_uuid;
    time_t timestamp;
    char title[MAX_NAME_LENGTH];
    char body[MAX_BODY_LENGTH];
} thread_info_t;

typedef struct reply_info {
    uuid_t thread_uuid;
    uuid_t user_uuid;
    uuid_t team_uuid;
    time_t timestamp;
    char body[MAX_BODY_LENGTH];
} reply_info_t;

typedef struct message_info {
    uuid_t sender_uuid;
    time_t timestamp;
    char body[MAX_BODY_LENGTH];
} message_info_t;

typedef struct user_info {
    uuid_t user_uuid;
    char name[MAX_NAME_LENGTH];
    int status;
} user_info_t;
