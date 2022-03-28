#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling (const char* msg);

int main(int argc, char* argv[])
{
    int sock;
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling ("socket() err");

    struct sockaddr_in serv_addr;

    char message[30];

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(atoi(argv[1]));
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*) &serv_addr, (socklen_t) sizeof(serv_addr)) == -1)
        error_handling ("connect() err");

    if(read(sock, message, sizeof(message)) == -1)
        error_handling ("read() err");

    fputs(message, stdout);

    return 0;
}

void error_handling (const char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}