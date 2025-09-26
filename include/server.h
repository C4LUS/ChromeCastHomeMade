#ifndef SERVER_H
    #define SERVER_H
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netdb.h>
    #include <netinet/in.h>
    #define SA struct sockaddr

int create_socket();
#endif