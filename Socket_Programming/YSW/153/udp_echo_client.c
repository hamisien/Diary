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
    if(argc != 3) {
        printf("Usage: %s <IP ADDRESS> <PORT>\n", argv[0]);
        exit(1);
    }
    
    int sd;

    int recvbyte, sendbyte;

    char msg[] = "Hello";
    char recvmsg[BUF_SIZE];

    struct sockaddr_in sock_addr;

    socklen_t sock_addr_size;  

    if((sd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
        err_handling("sockeet() err");
    }

    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inet_addr(argv[1]);
    sock_addr.sin_port = htons(atoi(argv[2]));

    /* sizeof(msg)보단 strlen(msg)로 하는 게 더 나은 것 같다.. */
    if((sendbyte = sendto(sd, msg, strlen(msg), 0, (struct sockaddr*) &sock_addr, sizeof(sock_addr))) == -1) {
        err_handling("sendto() err");
    } else {
        printf("sendbyte: %d\n", sendbyte);
    }

    if((recvbyte = recvfrom(sd, recvmsg, BUF_SIZE, 0, NULL, 0)) == -1) {
        err_handling("recvfrom() err");
    } else {
        printf("recvbyte: %d\n", recvbyte);
    }

    fputs(recvmsg, stdout);
    fputc('\n', stdout);

    close(sd);

    return 0;
}

void err_handling(char* msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}