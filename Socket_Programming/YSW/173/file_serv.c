#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUF_SIZE 50

void error_handling(char* msg);

int main(int argc, char* argv[]) 
{
    if(argc != 2) {
        printf("Usage: %s <PORT>", argv[0]);
        exit(1);
    }

    FILE* fd = fopen("file_serv.c", "r");;
    int serv_sd, clnt_sd;
    char buf[BUF_SIZE];

    struct sockaddr_in serv_addr, clnt_addr;

    socklen_t clnt_addr_size;

    if((serv_sd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        error_handling("socket() err");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind() err");
    }

    if(listen(serv_sd, 5) == -1) {
        error_handling("listen() err");
    }

    clnt_addr_size = sizeof(clnt_addr);

    clnt_sd = accept(serv_sd, (struct sockaddr*) &clnt_addr, &clnt_addr_size);

    fwrite(buf, sizeof(char), BUF_SIZE, fd);
    write(clnt_sd, buf, sizeof(buf));

    if(shutdown(clnt_sd, SHUT_WR) == -1) {
        error_handling("shutdown() err");
    }

    fclose(fd);
    close(clnt_sd);
    close(serv_sd);

    return 0;
}

void error_handling(char* msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);

    exit(1);
}