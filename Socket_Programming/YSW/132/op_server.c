#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024

void error_handling (const char* msg);

int main(int argc, const char* argv[])
{
    int serv_sock;
    int clnt_sock;
    int strlen;

    struct sockaddr_in serv_addr, clnt_addr;

    socklen_t clnt_sock_size;

    int msg[BUF_SIZE];

    if ((serv_sock = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        error_handling ("socket() err");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, &serv_addr, sizeof(serv_addr)) == -1) {
        error_handling ("bind() err");
    }

    if (listen(serv_sock, 5) == -1) {
        error_handling ("listen() err");
    }

    clnt_sock_size = sizeof(clnt_sock);

    if ((clnt_sock = accept(serv_sock, &clnt_addr, &clnt_sock_size)) == -1) {
        error_handling ("accept() err");
    }

    puts("Connected..");

    if ((strlen = read(clnt_sock, msg, sizeof(msg))) == -1) {
        error_handling ("read() err");
    }

    int op_cnt = msg[0];
    int oprnd[BUF_SIZE];
    for (int i = 0; i < op_cnt; i++) {
        oprnd[i] = msg[i+1];
    }
    int oprtr = msg[strlen];

    int result = 

    if (write(clnt_sock, ))

    return 0;
}

void error_handling (const char* msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}