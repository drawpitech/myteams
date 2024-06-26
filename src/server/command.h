/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** command
*/

#pragma once

#include "server.h"

void cmd_create(server_t *server, client_t *client);
void create_teams(server_t *server, client_t *client);
void create_channel(server_t *server, client_t *client);
void create_thread(server_t *server, client_t *client);

void cmd_login(server_t *server, client_t *client);
void cmd_logout(server_t *server, client_t *client);
void cmd_use(server_t *server, client_t *client);
void cmd_user(server_t *server, client_t *client);
void cmd_users(server_t *server, client_t *client);
void cmd_list(server_t *server, client_t *client);

void cmd_subscribe(server_t *server, client_t *client);
void cmd_unsubscribe(server_t *server, client_t *client);
void cmd_subscribed(server_t *server, client_t *client);

void cmd_info(server_t *server, client_t *client);

void cmd_send(server_t *server, client_t *client);
void cmd_messages(server_t *server, client_t *client);

static const struct cmd_s {
    char *name;
    void (*func)(server_t *server, client_t *client);
    char *description;
} COMMANDS[] = {
    {"CREATE", cmd_create, "based on the context, create the sub resource"},
    {"HELP", NULL, "show help information"},
    {"INFO", cmd_info,
        "based on the context, display details of the current resource"},
    {"LIST", cmd_list, "based on the context, list all the sub resources"},
    {"LOGIN", cmd_login, "set the user_name used by client"},
    {"LOGOUT", cmd_logout, "disconnect the client from the server"},
    {"MESSAGES", cmd_messages, "list all messages exchanged with the "
        "specified user"},
    {"SEND", cmd_send, "send a message to specific user"},
    {"SUBSCRIBE", cmd_subscribe, "subscribe to the events of a team and its "
        "sub directories (enable reception of all events from a team)"},
    {"SUBSCRIBED", cmd_subscribed, "list all subscribed teams or list all "
        "users subscribed to a team"},
    {"UNSUBSCRIBE", cmd_unsubscribe, "unsubscribe from a team"},
    {"USE", cmd_use, "sets the command context to a team/channel/thread"},
    {"USER", cmd_user, "get details about the requested user"},
    {"USERS", cmd_users, "get the list of all users that exist on the domain"},
};

void exec_command(server_t *server, client_t *client);
