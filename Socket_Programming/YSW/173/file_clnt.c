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
    if(argc != 3) {
        printf("Usage: %s <IP ADDRESS> <PORT>", argv[0]);
        exit(1);
    }

    FILE fd;
    int sd;
    char buf[BUF_SIZE];

    struct sockaddr_in serv_addr;

    int readnum;

    if((sd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        error_handling("socket() err");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() err");
    }

    if((readnum = read(sd, buf, sizeof(buf))) == -1) {
        error_handling("read() err");
    }

    printf("readnum = %d\n", readnum);
    printf("Received string data: %s\n", buf);

    // fclose();
    close(sd);

    return 0;
}

void error_handling(char* msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);

    exit(1);
}