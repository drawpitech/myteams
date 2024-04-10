/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** server
*/

#include "server.h"

#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "utils.h"

/**
 * @brief Append an element to an array.
 * @param array array in which to perform the operation
 * @param size_t size of ONE element of the array (sizeof char/int/...)
 * @param elem element to append
 * @warning This function is not safe. Is is made to perfom operations
 * on structures that share the same structure:
 * struct {
 *   size_t size;  // number of elements
 *   size_t alloc; // real size of the array
 *   T *array;
 * }
 */
static void append_to_array(void *array, size_t size, void *elem)
{
    size_t *d = array;
    size_t *nmemb = &d[0];
    size_t *alloc = &d[1];
    uint8_t **arr = (uint8_t **)&(d[2]);

    if (*nmemb + 1 > *alloc) {
        *alloc = (*alloc) ? *alloc * *alloc : 2;
        *arr = reallocarray(*arr, *alloc + 1, size);
        if (*arr == NULL)
            exit(0);
    }
    memcpy(*arr + *nmemb, elem, size);
    *nmemb += 1;
}

static bool new_client(server_t *serv, client_t *client)
{
    struct timeval tv = {.tv_sec = 1, .tv_usec = 1000};
    fd_set fdread;
    fd_set fdwrite;
    int sock = serv->fd;

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_SET(sock, &fdread);
    FD_SET(sock, &fdwrite);
    if (select(sock + 1, &fdread, &fdwrite, NULL, &tv) <= 0)
        return false;
    memset(client, 0, sizeof *client);
    socklen_t addr_len = sizeof(client->addr);
    client->fd = accept(sock, (struct sockaddr *)&client->addr, &addr_len);
    return client->fd != -1;
}

static bool parse_args(server_t *serv, int argc, char **argv)
{
    char *ptr = NULL;
    long port = 0;

    if (argc != 2) {
        fprintf(stderr, "Invalid number of arguments.\nUse -help for help\n");
        return false;
    }
    if (strcmp(argv[1], "-help") == 0) {
        printf(
            "USAGE: %s port\n\n"
            "\tport is the port number on which the server socket listens.\n",
            argv[0]);
        return false;
    }
    if (strlen(argv[1]) > 5) {
        fprintf(stderr, "Invalid port number.\n");
        return false;
    }
    ptr = argv[1];
    port = strtol(argv[1], &ptr, 10);
    if (*ptr != '\0' || port < 0 || port > UINT16_MAX) {
        fprintf(stderr, "Invalid port number.\n");
        return false;
    }
    serv->port = (uint16_t)port;
    return true;
}

static bool open_server(server_t *serv)
{
    serv->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (serv->fd < 0) {
        perror("socket");
        return false;
    }
    serv->addr = (struct sockaddr_in){
        .sin_family = AF_INET,
        .sin_port = htons(serv->port),
        .sin_addr.s_addr = INADDR_ANY,
    };
    if (bind(serv->fd, (struct sockaddr *)&serv->addr, sizeof(serv->addr)) < 0) {
        perror("bind");
        return false;
    }
    if (listen(serv->fd, 5) < 0) {
        perror("listen");
        return false;
    }
    return true;
}

int myteams_server(UNUSED int argc, UNUSED char **argv)
{
    server_t serv = {0};

    if (!parse_args(&serv, argc, argv) || !open_server(&serv))
        return 84;
    printf("Server running on port %d\n", serv.port);
    for (client_t client = {0};;) {
        if (new_client(&serv, &client))
            append_to_array(&serv.clients, sizeof client, &client);
    }
}
