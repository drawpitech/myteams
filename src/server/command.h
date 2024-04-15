/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** command
*/

#pragma once

#include "server.h"

void cmd_create(server_t *server, client_t *client);
void cmd_login(server_t *server, client_t *client);
void cmd_logout(server_t *server, client_t *client);
void cmd_user(server_t *server, client_t *client);

static const struct cmd_s {
    char *name;
    void (*func)(server_t *server, client_t *client);
    char *description;
} COMMANDS[] = {
    {"CREATE", cmd_create, "based on the context, create the sub resource"},
    {"HELP", NULL, "show help information"},
    {"INFO", NULL,
        "based on the context, display details of the current resource"},
    {"LIST", NULL, "based on the context, list all the sub resources"},
    {"LOGIN", cmd_login, "set the user_name used by client"},
    {"LOGOUT", cmd_logout, "disconnect the client from the server"},
    {"MESSAGES", NULL, "list all messages exchanged with the specified user"},
    {"SEND", NULL, "send a message to specific user"},
    {"SUBSCRIBE", NULL, "subscribe to the events of a team and its sub "
        "directories (enable reception of all events from a team)"},
    {"SUBSCRIBED", NULL, "list all subscribed teams or list all users "
        "subscribed to a team"},
    {"UNSUBSCRIBE", NULL, "unsubscribe from a team"},
    {"USE", NULL, "sets the command context to a team/channel/thread"},
    {"USER", cmd_user, "get details about the requested user"},
    {"USERS", NULL, "get the list of all users that exist on the domain"},
};

void exec_command(server_t *server, client_t *client);
