/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** server
*/

#pragma once

#include <stdbool.h>
#include <uuid/uuid.h>

#include "utils.h"

typedef struct {
    uuid_t *uuid;
    uuid_t *author_uuid;
    char message[MAX_BODY_LENGTH];
} comment_t;

typedef struct {
    uuid_t *uuid;
    char title[MAX_NAME_LENGTH];
    char message[MAX_BODY_LENGTH];
    struct {
        comment_t *arr;
        size_t size;
    } comment;
} thread_t;

typedef struct {
    uuid_t *uuid;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    struct {
        thread_t *arr;
        size_t size;
    } threads;
} channel_t;

typedef struct {
    uuid_t *uuid;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    struct {
        uuid_t **arr;
        size_t size;
    } users;
    struct {
        channel_t *arr;
        size_t size;
    } channels;
} team_t;

typedef struct {
    uuid_t *uuid;
    struct {
        uuid_t **arr;
        size_t size;
    } users;
} discussion_t;

typedef struct {
    uuid_t *uuid;
    char name[MAX_NAME_LENGTH];
    bool logged;
    uuid_t *team_uuid;
    uuid_t *channel_uuid;
    uuid_t *thread_uuid;
} user_t;

typedef struct {
    struct {
        team_t *arr;
        size_t size;
    } teams;
    struct {
        discussion_t *arr;
        size_t size;
    } discussions;
    struct {
        user_t *arr;
        size_t size;
    } users;
} server_t;

int myteams_server(int argc, char **argv);
