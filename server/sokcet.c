#include "../include/server.h"

int create_socket()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        printf("socket creation failed...\n");
        exit(0);
    }
    printf("socket created successfully created...\n");
    return sockfd;
}