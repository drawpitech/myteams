/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** server
*/

#include "server.h"

#include <netinet/in.h>
#include <netinet/ip.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "client.h"
#include "save/save.h"

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
void append_to_array(void *array, size_t size, void *elem)
{
    struct
    {
        size_t size;
        size_t alloc;
        uint8_t *array;
    } *arr = array;

    if (arr->size + 1 > arr->alloc) {
        arr->alloc = (arr->alloc) ? arr->alloc * arr->alloc : 2;
        arr->array = reallocarray(arr->array, arr->alloc + 1, size);
        if (arr->array == NULL)
            exit(0);
    }
    memcpy(arr->array + (arr->size * size), elem, size);
    arr->size += 1;
}

static bool new_client(server_t *serv, client_t *client)
{
    socklen_t addr_len = sizeof(client->addr);
    struct timeval tv = {.tv_sec = 0, .tv_usec = 100};
    fd_set fdread;
    fd_set fdwrite;
    int fd;

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_SET(serv->fd, &fdread);
    FD_SET(serv->fd, &fdwrite);
    if (select(serv->fd + 1, &fdread, &fdwrite, NULL, &tv) <= 0)
        return false;
    memset(client, 0, sizeof *client);
    fd = accept(serv->fd, (struct sockaddr *)&client->addr, &addr_len);
    if (fd < 0) {
        perror("accept");
        return false;
    }
    client_init(client, fd);
    return true;
}

static bool parse_port(server_t *serv, char *port)
{
    char *ptr = port;
    long p = strtol(port, &ptr, 10);

    if (*ptr != '\0' || p < 0 || p > UINT16_MAX) {
        fprintf(stdout, "Invalid port number.\n");
        return false;
    }
    serv->port = (uint16_t)p;
    return true;
}

static bool parse_args(server_t *serv, int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stdout, "Invalid number of arguments.\nUse -help for help\n");
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
        fprintf(stdout, "Invalid port number.\n");
        return false;
    }
    return parse_port(serv, argv[1]);
}

static bool open_server(server_t *s)
{
    s->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (s->fd < 0) {
        perror("socket");
        return false;
    }
    if (setsockopt(s->fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) ==
        -1)
        return false;
    s->addr = (struct sockaddr_in){
        .sin_family = AF_INET,
        .sin_port = htons(s->port),
        .sin_addr.s_addr = INADDR_ANY,
    };
    if (bind(s->fd, (struct sockaddr *)&s->addr, sizeof(s->addr)) < 0 ||
        listen(s->fd, 5) < 0) {
        perror("bind/listen");
        close(s->fd);
        return false;
    }
    return true;
}

int myteams_server(int argc, char **argv)
{
    server_t serv = {0};

    if (!parse_args(&serv, argc, argv) || !open_server(&serv))
        return 84;
    load_server(&serv);
    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigint);
    printf("Server running on port %d\n", serv.port);
    set_running_state(true);
    for (client_t client = {0}; get_running_state();) {
        if (new_client(&serv, &client))
            append_to_array(&serv.clients, sizeof client, &client);
        for (size_t i = 0; i < serv.clients.size; ++i)
            handle_client(&serv, &serv.clients.arr[i]);
    }
    for (size_t i = 0; i < serv.clients.size; ++i)
        client_disconnect(&serv.clients.arr[i]);
    save_server(&serv);
    free_server(&serv);
    return SUCCESS;
}
