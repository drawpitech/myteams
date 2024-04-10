/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** command
*/

#pragma once

typedef struct cmd_conv {
    char *cmd;
    char *conv;
} cmd_conv_t;

static const cmd_conv_t commands[] = {
    {"/help", "HELP"},
    {"/login", "LOGIN"},
    {"/logout", "LOGOUT"},
    {"/users", "USERS"},
    {"/user", "USER"},
    {"/send", "SEND"},
    {"/messages", "MESSAGES"},
    {"/subscribe", "SUBSCRIBE"},
    {"/subscribed", "SUBSCRIBED"},
    {"/unsubscribed", "UNSUBSCRIBED"},
    {"/use", "USE"},
    {"/create", "CREATE"},
    {"/list", "LIST"},
    {"/info", "INFO"},
};
