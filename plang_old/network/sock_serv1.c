#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling (const char* msg);

int main(int argc, char* argv[])
{
    int sock_serv; /* socket() */
    int sock_clnt; /* accept() */

    char message[] = "Hello, socket!";

    socklen_t clnt_addr_len;

    if (argc != 2) {
        printf ("Usage: %s <PORT>\n", argv[0]);
        exit(1);
    }

    sock_serv = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_serv == -1)
        error_handling ("socket() err");

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));


    if (bind(sock_serv, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() err");

    if(listen(sock_serv, 5) != 0) 
        error_handling ("listen() err");
    
    if((sock_clnt = accept(sock_serv, (struct sockaddr*) &clnt_addr, (socklen_t *) sizeof(clnt_addr))) == -1)
        error_handling ("accept() err");


    write (sock_serv, message, sizeof(message));

    close (sock_clnt);
    close (sock_serv);

    return 0;
}

void error_handling (const char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}