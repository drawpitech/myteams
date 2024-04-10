/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** server
*/

#pragma once

#include <linux/limits.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
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
        size_t size;
        size_t alloc;
        comment_t *arr;
    } comment;
} thread_t;

typedef struct {
    uuid_t *uuid;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    struct {
        size_t size;
        size_t alloc;
        thread_t *arr;
    } threads;
} channel_t;

typedef struct {
    uuid_t *uuid;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    struct {
        size_t size;
        size_t alloc;
        uuid_t **arr;
    } users;
    struct {
        size_t size;
        size_t alloc;
        channel_t *arr;
    } channels;
} team_t;

typedef struct {
    uuid_t *uuid;
    struct {
        size_t size;
        size_t alloc;
        uuid_t **arr;
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
    int fd;
    struct sockaddr_in addr;
    socklen_t len;
    user_t user;
    char buffer_cmd[BUFSIZ];
} client_t;

typedef struct {
    struct {
        size_t size;
        size_t alloc;
        team_t *arr;
    } teams;
    struct {
        discussion_t *arr;
        size_t size;
    } discussions;
    struct {
        size_t size;
        size_t alloc;
        client_t *arr;
    } clients;
    int fd;
    uint16_t port;
    struct sockaddr_in addr;
} server_t;

int myteams_server(int argc, char **argv);
void handle_client(server_t *serv, client_t *client);
