/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** getters
*/

#include <string.h>

#include "server.h"

user_t *get_user_by_uuid(server_t *server, uuid_t uuid)
{
    user_t *user = NULL;

    for (size_t i = 0; i < server->clients.size; i++) {
        user = server->clients.arr[i].user;
        if (user != NULL && memcmp(user->uuid, uuid, sizeof(uuid_t)) == 0)
            return user;
    }
    return NULL;
}

team_t *get_team_by_uuid(server_t *server, uuid_t uuid)
{
    team_t *team = NULL;

    for (size_t i = 0; i < server->teams.size; i++) {
        team = &server->teams.arr[i];
        if (memcmp(team->uuid, uuid, sizeof(uuid_t)) == 0)
            return team;
    }
    return NULL;
}

channel_t *get_channel_by_uuid(team_t *team, uuid_t uuid)
{
    channel_t *channel = NULL;

    for (size_t i = 0; i < team->channels.size; i++) {
        channel = &team->channels.arr[i];
        if (memcmp(channel->uuid, uuid, sizeof(uuid_t)) == 0)
            return channel;
    }
    return NULL;
}

thread_t *get_thread_by_uuid(channel_t *channel, uuid_t uuid)
{
    thread_t *thread = NULL;

    for (size_t i = 0; i < channel->threads.size; i++) {
        thread = &channel->threads.arr[i];
        if (memcmp(thread->thread_uuid, uuid, sizeof(uuid_t)) == 0)
            return thread;
    }
    return NULL;
}
