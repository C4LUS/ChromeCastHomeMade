#include "../include/server.h"

void setup(int port, int sockfd)
{
    struct sockaddr_in servaddr;
   
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(84);
    }
    printf("socket successfully binded...\n");
}

int connection(int sockfd) {
    struct sockaddr_in cli;
    int len = 0;
    int con_fd = 0;
    
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(84);
    } else
        printf("Server Listening...\n");
    len = sizeof(cli);

    if ((con_fd = accept(sockfd, (SA*)&cli, &len)) < 0) {
        printf("Server accept failed...\n");
        exit(84);
    } else 
        printf("Server accept the client...\n");
    return con_fd;
}

void func(int con_fd)
{
    char buff[80]; 
    int n; 
    // infinite loop for chat 
    for (;;) { 
        bzero(buff, 80); 
  
        // read the message from client and copy it in buffer 
        read(con_fd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf("From client: %s\t To client : ", buff); 
        bzero(buff, 80); 
        n = 0; 
        // copy server message in the buffer 
        while ((buff[n++] = getchar()) != '\n') 
            ; 
  
        // and send that buffer to client 
        write(con_fd, buff, sizeof(buff)); 
  
        // if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
}

int main (int ac, char **av) {
    int sockfd = create_socket();
    setup(atoi(av[1]), sockfd);
    int con_fd = connection(sockfd);
    func(con_fd);
    close(sockfd);
    return 0;
}