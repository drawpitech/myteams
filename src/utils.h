/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** utils
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

#define ERROR 84
#define SUCCESS 0
#define LEN_OF(x) (sizeof(x) / sizeof(*x))

#define MSG_ERR(x) dprintf(STDERR_FILENO, x), ERROR
#define MSG_ERR_V(x, ...) dprintf(STDERR_FILENO, x, __VA_ARGS__), ERROR
