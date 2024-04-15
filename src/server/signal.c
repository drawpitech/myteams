/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** signal
*/

#include <stdlib.h>

#include "server.h"

void handle_sigint(int sig)
{
    (void)sig;
    exit(0);
}
