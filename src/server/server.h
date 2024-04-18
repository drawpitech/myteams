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
#include <time.h>
#include <unistd.h>
#include <uuid/uuid.h>

#include "utils.h"

typedef struct {
    uuid_t uuid;
    uuid_t author_uuid;
    char message[MAX_BODY_LENGTH];
} comment_t;

typedef struct {
    uuid_t thread_uuid;
    uuid_t author_uuid;
    time_t timestamp;
    char title[MAX_NAME_LENGTH];
    char body[MAX_BODY_LENGTH];
    struct {
        size_t size;
        size_t alloc;
        comment_t *arr;
    } comments;
} thread_t;

typedef struct {
    uuid_t uuid;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    struct {
        size_t size;
        size_t alloc;
        thread_t *arr;
    } threads;
} channel_t;

typedef struct {
    uuid_t uuid;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    struct {
        size_t size;
        size_t alloc;
        uuid_t *arr;
    } users;
    struct {
        size_t size;
        size_t alloc;
        channel_t *arr;
    } channels;
} team_t;

typedef struct {
    uuid_t sender_uuid;
    char body[MAX_BODY_LENGTH];
    time_t timestamp;
} message_t;

typedef struct {
    uuid_t user_1uuid;
    uuid_t user_2uuid;
    struct {
        size_t size;
        size_t alloc;
        message_t *arr;
    } messages;
} discussion_t;

typedef struct {
    uuid_t uuid;
    char name[MAX_NAME_LENGTH];
    int status;
} user_t;

typedef struct {
    int fd;
    struct sockaddr_in addr;
    socklen_t len;
    uuid_t user;
    char buffer[BUFSIZ];
    uuid_t team;
    uuid_t channel;
    uuid_t thread;
} client_t;

typedef struct {
    struct {
        size_t size;
        size_t alloc;
        team_t *arr;
    } teams;
    struct {
        size_t size;
        size_t alloc;
        discussion_t *arr;
    } discussions;
    struct {
        size_t size;
        size_t alloc;
        client_t *arr;
    } clients;
    struct {
        size_t size;
        size_t alloc;
        user_t *arr;
    } users;
    int fd;
    uint16_t port;
    struct sockaddr_in addr;
} server_t;

int myteams_server(int argc, char **argv);

user_t *get_user_by_uuid(server_t *server, uuid_t uuid);
team_t *get_team_by_uuid(server_t *server, uuid_t uuid);
channel_t *get_channel_by_uuid(team_t *team, uuid_t uuid);
thread_t *get_thread_by_uuid(channel_t *channel, uuid_t uuid);

void append_to_array(void *array, size_t size, void *elem);
void handle_sigint(int sig);
bool get_running_state(void);
void set_running_state(bool state);
void free_server(server_t *server);
