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
    uuid_t team_uuid;
    char team_name[MAX_NAME_LENGTH];
    char team_description[MAX_DESCRIPTION_LENGTH];
} team_info_t;

typedef struct channel_info {
    uuid_t channel_uuid;
    char channel_name[MAX_NAME_LENGTH];
    char channel_description[MAX_DESCRIPTION_LENGTH];
} channel_info_t;

typedef struct thread_info {
    uuid_t thread_uuid;
    uuid_t user_uuid;
    time_t thread_timestamp;
    char thread_title[MAX_NAME_LENGTH];
    char thread_body[MAX_BODY_LENGTH];
} thread_info_t;

typedef struct reply_info {
    uuid_t thread_uuid;
    uuid_t user_uuid;
    uuid_t team_uuid;
    time_t reply_timestamp;
    char reply_body[MAX_BODY_LENGTH];
} reply_info_t;

typedef struct message_info {
    uuid_t sender_uuid;
    time_t message_timestamp;
    char message_body[MAX_BODY_LENGTH];
} message_info_t;

typedef struct user_info {
    uuid_t user_uuid;
    char user_name[MAX_NAME_LENGTH];
    int user_status;
} user_info_t;
