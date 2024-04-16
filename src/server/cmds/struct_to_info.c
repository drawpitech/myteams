/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** struct_to_info
*/

#include <stddef.h>
#include <string.h>
#include <uuid/uuid.h>

#include "cmds_utils.h"
#include "ressources_infos.h"
#include "server.h"

user_info_t *user_to_info(user_t *user, user_info_t *info)
{
    if (user == NULL || info == NULL)
        return NULL;
    memset(info, 0, sizeof *info);
    if (user->status > 0)
        info->status = 1;
    strcpy(info->name, user->name);
    uuid_copy(info->user_uuid, user->uuid);
    return info;
}

team_info_t *team_to_info(team_t *team, team_info_t *info)
{
    if (team == NULL || info == NULL)
        return NULL;
    memset(info, 0, sizeof *info);
    strcpy(info->description, team->description);
    strcpy(info->name, team->name);
    uuid_copy(info->uuid, team->uuid);
    return info;
}

channel_info_t *channel_to_info(channel_t *channel, channel_info_t *info)
{
    if (channel == NULL || info == NULL)
        return NULL;
    memset(info, 0, sizeof *info);
    strcpy(info->description, channel->description);
    strcpy(info->name, channel->name);
    uuid_copy(info->uuid, channel->uuid);
    return info;
}

thread_info_t *thread_to_info(thread_t *thread, thread_info_t *info)
{
    if (thread == NULL || info == NULL)
        return NULL;
    memset(info, 0, sizeof *info);
    strcpy(info->body, thread->body);
    strcpy(info->title, thread->title);
    uuid_copy(info->thread_uuid, thread->thread_uuid);
    uuid_copy(info->user_uuid, thread->author_uuid);
    info->timestamp = thread->timestamp;
    return info;
}

reply_info_t *comment_to_info(
    comment_t *reply, reply_info_t *info, thread_t *thread, team_t *team)
{
    if (reply == NULL || info == NULL)
        return NULL;
    memset(info, 0, sizeof *info);
    strcpy(info->body, reply->message);
    uuid_copy(info->thread_uuid, thread->thread_uuid);
    uuid_copy(info->team_uuid, team->uuid);
    uuid_copy(info->user_uuid, reply->author_uuid);
    return info;
}
