/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** free
*/

#include <stdlib.h>

#include "server.h"

static void free_discussion(discussion_t *discussion)
{
    if (discussion == NULL)
        return;
    if (discussion->messages.arr != NULL)
        free(discussion->messages.arr);
}

static void free_thread(thread_t *thread)
{
    if (thread == NULL)
        return;
    if (thread->comments.arr != NULL)
        free(thread->comments.arr);
}

static void free_channel(channel_t *channel)
{
    if (channel == NULL)
        return;
    if (channel->threads.arr != NULL) {
        for (size_t i = 0; i < channel->threads.size; ++i)
            free_thread(&channel->threads.arr[i]);
        free(channel->threads.arr);
    }
}

static void free_team(team_t *team)
{
    if (team == NULL)
        return;
    if (team->users.arr != NULL)
        free(team->users.arr);
    if (team->channels.arr != NULL) {
        for (size_t i = 0; i < team->channels.size; ++i)
            free_channel(&team->channels.arr[i]);
        free(team->channels.arr);
    }
}

void free_server(server_t *server)
{
    if (server == NULL)
        return;
    if (server->clients.arr != NULL)
        free(server->clients.arr);
    if (server->users.arr != NULL)
        free(server->users.arr);
    if (server->discussions.arr != NULL) {
        for (size_t i = 0; i < server->discussions.size; ++i)
            free_discussion(&server->discussions.arr[i]);
        free(server->discussions.arr);
    }
    if (server->teams.arr != NULL) {
        for (size_t i = 0; i < server->teams.size; ++i)
            free_team(&server->teams.arr[i]);
        free(server->teams.arr);
    }
}
