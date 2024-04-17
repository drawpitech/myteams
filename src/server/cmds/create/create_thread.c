/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** create_thread
*/

#include <myteams/logging_client.h>
#include <myteams/logging_server.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <uuid/uuid.h>

#include "cmds/cmds_utils.h"
#include "command.h"
#include "ressources_infos.h"
#include "server.h"

static void send_to_users(server_t *server, team_t *team, thread_info_t *info)
{
    for (size_t i = 0; i < server->clients.size; i++) {
        if (server->clients.arr[i].fd == -1 ||
            !user_in_team(&server->clients.arr[i], team))
            continue;
        write(server->clients.arr[i].fd, "343", 3);
        write(server->clients.arr[i].fd, info, sizeof(*info));
    }
}

static void send_messages(server_t *server, client_t *client, thread_t *thread)
{
    thread_info_t info = {0};
    char thread_uuid[UUID_STR_LEN] = {0};
    char channel_uuid[UUID_STR_LEN] = {0};
    char user_uuid[UUID_STR_LEN] = {0};

    uuid_unparse(thread->thread_uuid, thread_uuid);
    uuid_unparse(client->channel->uuid, channel_uuid);
    uuid_unparse(client->user->uuid, user_uuid);
    server_event_thread_created(
        channel_uuid, thread_uuid, user_uuid, thread->title, thread->body);
    write(client->fd, "213", 3);
    write(client->fd, thread_to_info(thread, &info), sizeof(info));
    send_to_users(server, client->team, &info);
}

static void create_new_thread(
    server_t *server, client_t *client, const char name[],
    const char description[])
{
    thread_t thread = {0};

    if (!name || !description)
        return;
    thread.timestamp = time(NULL);
    strcpy(thread.title, name);
    strcpy(thread.body, description);
    uuid_generate(thread.thread_uuid);
    uuid_copy(thread.author_uuid, client->user->uuid);
    append_to_array(&client->channel->threads, sizeof(thread_t), &thread);
    send_messages(server, client, &thread);
}

static bool thread_already_exist(
    channel_t *channel, client_t *client, char *name)
{
    for (size_t i = 0; name && i < channel->threads.size; i++) {
        if (strcmp(name, channel->threads.arr[i].title) == 0) {
            dprintf(client->fd, "530\n");
            return true;
        }
    }
    return false;
}

void create_thread(server_t *server, client_t *client)
{
    char *name = NULL;
    char *description = NULL;
    size_t arg_pos = 0;

    name = get_quoted_arg(client->buffer, 0, &arg_pos);
    arg_pos += 1;
    if (name && thread_already_exist(client->channel, client, name))
        return;
    if (name) {
        description = get_quoted_arg(client->buffer, arg_pos, &arg_pos);
        if (description) {
            create_new_thread(server, client, name, description);
            return;
        }
    }
    dprintf(client->fd, "502 Syntax error.\n");
}
