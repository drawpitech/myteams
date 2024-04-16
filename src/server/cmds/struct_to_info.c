/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** struct_to_info
*/

#include "cmds_utils.h"

#include "ressources_infos.h"
#include "server.h"
#include <stddef.h>
#include <string.h>

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
