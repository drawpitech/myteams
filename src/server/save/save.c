/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** save
*/

#include "save.h"

#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "server.h"

static void save_data_threads(int fd, channel_t *channel)
{
    thread_t *thread = NULL;
    thread_t copy = {0};

    for (size_t i = 0; i < channel->threads.size; i++) {
        thread = &channel->threads.arr[i];
        copy = *thread;
        copy.comments.arr = NULL;
        write(fd, &copy, sizeof copy);
        write(
            fd, thread->comments.arr,
            thread->comments.size * sizeof *thread->comments.arr);
    }
}

static void save_data_channels(int fd, team_t *team)
{
    channel_t *channel = NULL;
    channel_t copy = {0};

    for (size_t i = 0; i < team->channels.size; i++) {
        channel = &team->channels.arr[i];
        copy = *channel;
        copy.threads.arr = NULL;
        write(fd, &copy, sizeof copy);
        save_data_threads(fd, channel);
    }
}

static void save_data_teams(int fd, server_t *server)
{
    team_t *team = NULL;
    team_t copy = {0};

    for (size_t i = 0; i < server->teams.size; i++) {
        team = &server->teams.arr[i];
        copy = *team;
        copy.channels.arr = NULL;
        write(fd, &copy, sizeof copy);
        write(fd, team->users.arr, team->users.size * sizeof *team->users.arr);
        save_data_channels(fd, team);
    }
}

static void save_data_discussions(int fd, server_t *server)
{
    discussion_t *discussion = NULL;
    discussion_t copy = {0};

    for (size_t i = 0; i < server->discussions.size; i++) {
        discussion = &server->discussions.arr[i];
        copy = *discussion;
        copy.messages.arr = NULL;
        write(fd, &copy, sizeof copy);
        write(
            fd, discussion->messages.arr,
            discussion->messages.size * sizeof *discussion->messages.arr);
    }
}

static void save_data_users(int fd, server_t *server)
{
    user_t copy;

    for (size_t i = 0; i < server->users.size; i++) {
        copy = server->users.arr[i];
        copy.status = 0;
        write(fd, &copy, sizeof copy);
    }
}

static void save_data_server(int fd, server_t *server)
{
    server_t copy = *server;

    copy.users.arr = NULL;
    copy.discussions.arr = NULL;
    copy.teams.arr = NULL;
    copy.clients.arr = NULL;
    copy.clients.size = 0;
    copy.clients.alloc = 0;
    write(fd, &copy, sizeof copy);
    save_data_users(fd, server);
    save_data_discussions(fd, server);
    save_data_teams(fd, server);
}

void save_server(server_t *server)
{
    int fd = open(DATA_FILE, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        perror("open");
        return;
    }
    save_data_server(fd, server);
    close(fd);
    printf("Saved to %s\n", DATA_FILE);
}
