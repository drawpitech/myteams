/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** signal
*/

#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "server.h"

static bool *aaah(void)
{
    static bool value = true;

    return &value;
}

void set_running_state(bool state)
{
    *aaah() = state;
}

bool get_running_state(void)
{
    return *aaah();
}

void handle_sigint(int sig)
{
    printf("Exiting with status %d...\n", sig);
    set_running_state(false);
}
