#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling (const char* msg);

int main(int argc, char* argv[])
{
    int sock_clnt;
    
    struct sockaddr_in serv_addr;

    memset(serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(atoi(argv[1]));
    serv_addr.sin_port = htons(atoi(argv[2]));

    sock_clnt = socket(AF_INET, SOCK_STREAM, 0);

    connect(sock_clnt, &serv_addr, (socklen_t) sizeof(serv_addr));

    read(sock_clnt);

    return 0;
}

void error_handling (const char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}