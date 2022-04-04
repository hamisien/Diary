#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling (const char* msg);

int main(int argc, const char* argv[])
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr, clnt_addr;

    socklen_t clnt_sock_size;

    if ((serv_sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        error_handling ("socket() err");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, &serv_addr, sizeof(serv_addr)) == -1)
        error_handling ("bind() err");

    if (listen(serv_sock, 5) == -1)
        error_handling ("listen() err");

    clnt_sock_size = sizeof()

    if (accept());

    return 0;
}

void error_handling (const char* msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}