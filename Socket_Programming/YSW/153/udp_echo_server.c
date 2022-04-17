#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BUF_SIZE 50

void err_handling(char* msg);

int main(int argc, char* argv[])
{
    if(argc != 2) {
        printf("Usage: %s <PORT>\n", argv[0]);
        exit(1);
    }

    int sd;

    int recvbyte, sendbyte;

    char msg[BUF_SIZE];

    struct sockaddr_in serv_addr, clnt_addr;

    socklen_t clnt_addr_size;

    if((sd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
        err_handling("socket() err");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(sd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
        err_handling("bind() err");
    }

    clnt_addr_size = sizeof(clnt_addr);

    if((recvbyte = recvfrom(sd, msg, BUF_SIZE, 0, (struct sockaddr*) &clnt_addr, &clnt_addr_size)) == -1) {
        err_handling("recvfrom() err");
    } else {
        printf("recvbyte: %d\n", recvbyte);
    }

    if((sendbyte = sendto(sd, msg, strlen(msg), 0, (struct sockaddr*) &clnt_addr, sizeof(clnt_addr))) == -1) {
        err_handling("sendto() err");
    } else {
        printf("sendbyte: %d\n", sendbyte);
    }

    close(sd);

    return 0;
}

void err_handling(char* msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}