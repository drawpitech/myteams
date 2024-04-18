/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** load
*/

#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "debug.h"
#include "save.h"
#include "server.h"

static void load_data_threads(int fd, channel_t *channel)
{
    thread_t *t = NULL;

    channel->threads.arr =
        malloc(channel->threads.alloc * sizeof *channel->threads.arr);
    for (size_t i = 0; i < channel->threads.size; i++) {
        t = &channel->threads.arr[i];
        read(fd, t, sizeof *t);
        t->comments.arr = malloc(t->comments.alloc * sizeof *t->comments.arr);
        read(fd, t->comments.arr, t->comments.alloc * sizeof *t->comments.arr);
    }
}

static void load_data_channels(int fd, team_t *team)
{
    channel_t *c = NULL;

    team->channels.arr =
        malloc(team->channels.alloc * sizeof *team->channels.arr);
    for (size_t i = 0; i < team->channels.size; i++) {
        c = &team->channels.arr[i];
        read(fd, c, sizeof *c);
        load_data_threads(fd, c);
    }
}

static void load_data_teams(int fd, server_t *server)
{
    team_t *t = NULL;

    server->teams.arr =
        malloc(server->teams.alloc * sizeof *server->teams.arr);
    for (size_t i = 0; i < server->teams.size; i++) {
        t = &server->teams.arr[i];
        read(fd, t, sizeof *t);
        t->users.arr = malloc(t->users.alloc * sizeof *t->users.arr);
        read(fd, t->users.arr, t->users.alloc * sizeof *t->users.arr);
        load_data_channels(fd, t);
    }
}

static void load_data_discussions(int fd, server_t *server)
{
    discussion_t *d = NULL;

    server->discussions.arr =
        malloc(server->discussions.alloc * sizeof *server->discussions.arr);
    for (size_t i = 0; i < server->discussions.size; i++) {
        d = &server->discussions.arr[i];
        read(fd, d, sizeof *d);
        d->messages.arr = malloc(d->messages.alloc * sizeof *d->messages.arr);
        read(fd, d->messages.arr, d->messages.alloc * sizeof *d->messages.arr);
    }
}

static void load_data_users(int fd, server_t *serv)
{
    serv->users.arr = malloc(serv->users.alloc * sizeof *serv->users.arr);
    read(fd, serv->users.arr, serv->users.alloc * sizeof *serv->users.arr);
}

static void load_data_server(int fd, server_t *server)
{
    read(fd, server, sizeof *server);
    load_data_users(fd, server);
    load_data_discussions(fd, server);
    load_data_teams(fd, server);
}

void load_server(server_t *server)
{
    int fd = open(DATA_FILE, O_RDONLY);

    if (fd == -1) {
        DEBUG_MSG("Failed to load config");
        return;
    }
    load_data_server(fd, server);
    close(fd);
    DEBUG("Reloaded to %s", DATA_FILE);
}
