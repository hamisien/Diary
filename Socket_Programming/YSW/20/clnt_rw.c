#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling (const char* msg);

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("Usage: %s <IP Address> <PORT>\n", argv[0]);
        exit(1);
    }

    int sock;
    int read_byte;
    struct sockaddr_in serv_addr;
    char message[30] = {0, };

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling ("socket() err");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // inet_addr!!
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling ("connect() err");

    if((read_byte = read(sock, message, sizeof(message))) == -1)
        error_handling ("read() err");

    // recv(sock, message, sizeof(message), 0);

    printf("read_byte: %d\nMessage from server: %s \n ", read_byte, message);
    // fputs(message, stdout);

    close (sock);

    return 0;
}

void error_handling (const char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}