/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** command
*/

#pragma once

#include "server.h"

static const struct cmd_s {
    char *name;
    int (*func)(server_t *server, client_t *client, const char *cmd);
    char *description;
} COMMANDS[] = {
    {"HELP", NULL, "show help information"},
    {"LOGIN", NULL, "set the user_name used by client"},
    {"LOGOUT", NULL, "disconnect the client from the server"},
    {"USERS", NULL, "get the list of all users that exist on the domain"},
    {"USER", NULL, "get details about the requested user"},
    {"SEND", NULL, "send a message to specific user"},
    {"MESSAGES", NULL, "list all messages exchanged with the specified user"},
    {"SUBSCRIBE", NULL,
        "subscribe to the events of a team and its sub directories (enable "
        "reception of all events from a team)"},
    {"SUBSCRIBED", NULL,
        "list all subscribed teams or list all users subscribed to a team"},
    {"UNSUBSCRIBED", NULL, "unsubscribe from a team"},
    {"USE", NULL, "sets the command context to a team/channel/thread"},
    {"CREATE", NULL, "based on the context, create the sub resource"},
    {"LIST", NULL,
        "based on the context, list all the sub resources (see below)"},
    {"INFO", NULL,
        "based on the context, display details of the current resource (see "
        "below)"},
};

void exec_command(UNUSED server_t *server, client_t *client);
