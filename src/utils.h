/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** server
*/

#pragma once

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#ifndef PROG
    #define PROG main
#endif
#define PROGNAME TOSTRING(PROG)

#define ATTR(x) __attribute__((x))
#define UNUSED ATTR(unused)

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
