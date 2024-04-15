/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** handle_event
*/

#pragma once


#include "client.h"
typedef struct func_code {
    char *code;
    int (*func)(connection_t *connect);
} func_code_t;

int receive_login(connection_t *connect);
int receive_logout(connection_t *connect);
int receive_message(connection_t *connect);
int receive_reply(connection_t *connect);
int receive_created_teams(connection_t *connect);
int receive_created_channel(connection_t *connect);
int receive_created_thread(connection_t *connect);


static const func_code_t func_code_tab[] = {
    {"311", &receive_login},
    {"312", &receive_logout},
    {"320", &receive_message},
    {"330", &receive_reply},
    {"341", &receive_created_teams},
    {"342", &receive_created_channel},
    {"343", &receive_created_thread},
};

int standard_error(connection_t *connect);
int unknown_team(connection_t *connect);
int unknown_channel(connection_t *connect);
int unknown_thread(connection_t *connect);
int unknown_user(connection_t *connect);

int error_unauthorized(connection_t *connect);
int error_already_exist(connection_t *connect);

static const func_code_t error_code_tab[] = {
    {"501", &standard_error},
    {"502", &standard_error},
    {"503", &standard_error},
    {"511", &unknown_team},
    {"512", &unknown_channel},
    {"513", &unknown_thread},
    {"514", &unknown_user},
    {"520", &error_unauthorized},
    {"530", &error_already_exist},
};
