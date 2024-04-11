/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** command
*/

#pragma once

#include "client.h"

typedef struct cmd_conv {
    char *cmd;
    char *conv;
    int (*func)(
        connection_t *connect, const char *cmd,
        const struct cmd_conv *command);
    char *help;
} cmd_conv_t;

int cmd_help(
    connection_t *connect, const char *cmd, const cmd_conv_t *command);
int cmd_login(
    connection_t *connect, const char *cmd, const cmd_conv_t *command);
int cmd_logout(
    connection_t *connect, const char *cmd, const cmd_conv_t *command);
int cmd_users(
    connection_t *connect, const char *cmd, const cmd_conv_t *command);
int cmd_user(
    connection_t *connect, const char *cmd, const cmd_conv_t *command);
int cmd_send(
    connection_t *connect, const char *cmd, const cmd_conv_t *command);
int cmd_messages(
    connection_t *connect, const char *cmd, const cmd_conv_t *command);
int cmd_subscribe(
    connection_t *connect, const char *cmd, const cmd_conv_t *command);
int cmd_subscribed(
    connection_t *connect, const char *cmd, const cmd_conv_t *command);
int cmd_unsubscribe(
    connection_t *connect, const char *cmd, const cmd_conv_t *command);
int cmd_use(connection_t *connect, const char *cmd, const cmd_conv_t *command);
int cmd_create(
    connection_t *connect, const char *cmd, const cmd_conv_t *command);
int cmd_list(
    connection_t *connect, const char *cmd, const cmd_conv_t *command);
int cmd_info(
    connection_t *connect, const char *cmd, const cmd_conv_t *command);

static const cmd_conv_t commands[] = {
    {"/help", "HELP", &cmd_help, "show help information"},
    {"/login", "LOGIN", &cmd_login, "set the user_name used by client"},
    {"/logout", "LOGOUT", &cmd_logout,
        "disconnect the client from the server"},
    {"/users", "USERS", &cmd_users,
        "get the list of all users that exist on the domain"},
    {"/user", "USER", &cmd_user, "get details about the requested user"},
    {"/send", "SEND", &cmd_send, "send a message to specific user"},
    {"/messages", "MESSAGES", &cmd_messages,
        "list all messages exchanged with the specified user"},
    {"/subscribe", "SUBSCRIBE", &cmd_subscribe,
        "subscribe to the events of a team and its sub directories (enable "
        "reception of all events from a team)"},
    {"/subscribed", "SUBSCRIBED", &cmd_subscribed,
        "list all subscribed teams or list all users subscribed to a team"},
    {"/unsubscribe", "UNSUBSCRIBED", &cmd_unsubscribe,
        "unsubscribe from a team"},
    {"/use", "USE", &cmd_use,
        "sets the command context to a team/channel/thread"},
    {"/create", "CREATE", &cmd_create,
        "based on the context, create the sub resource"},
    {"/list", "LIST", &cmd_list,
        "based on the context, list all the sub resources (see below)"},
    {"/info", "INFO", &cmd_info,
        "based on the context, display details of the current resource (see "
        "below)"},
};
