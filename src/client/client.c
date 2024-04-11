/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** client
*/

#include "client.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "utils.h"

static int open_socket(connection_t *connection, char *ip, int port)
{
    connection->sockaddr.sin_family = AF_INET;
    connection->sockaddr.sin_port = htons(port);
    connection->sockaddr.sin_addr.s_addr = inet_addr(ip);
    connection->servfd = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(
            connection->servfd, (struct sockaddr *)&connection->sockaddr,
            sizeof(connection->sockaddr)) == -1) {
        perror("Connect");
        return ERROR;
    }
    return SUCCESS;
}

int myteams_cli(int argc, char **argv)
{
    int port = 0;
    connection_t connect = {0};

    if (argc != 3 || !argv || !argv[1] || !argv[2]) {
        printf(
            "USAGE: ./myteams_cli ip port\n\tip is the server ip address on "
            "which the server socket listens\n\tport is the port number on "
            "which the server socket listens\n");
        return ERROR;
    }
    port = atoi(argv[2]);
    if (port <= 127)
        return MSG_ERR("Wrong port\n");
    if (open_socket(&connect, argv[1], port) != 0)
        return MSG_ERR("Link with server failed\n");
    return run_client(&connect);
}
