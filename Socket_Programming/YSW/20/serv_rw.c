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

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;

    socklen_t clnt_addr_size;

    char message[] = "Hello, socket!\n"; 
    /* (16바이트가 전송되는 이유는 개행 문자와 널문자 도합 2바이트가 추가되기 때문) */

    if (argc != 2) {
        printf ("Usage: %s <PORT>\n", argv[0]);
        exit(1);
    }

    sock_serv = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_serv == -1)
        error_handling ("socket() err");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));


    if (bind(sock_serv, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() err");

    if(listen(sock_serv, 5) == -1)
        error_handling ("listen() err");

    clnt_addr_size = sizeof(clnt_addr);
    
    if((sock_clnt = accept(sock_serv, (struct sockaddr*) &clnt_addr, &clnt_addr_size)) == -1)
        error_handling ("accept() err");
    /* if 함수의 소괄호 안에서 함수호출과 그 반환값을 변수에 대입할 때는 
        괄호를 분명하게 넣어서 인지하기 어려운 오류를 만들어내지 말자.. */

    printf("sizeof(message): %d\n", sizeof(message));
    write (sock_clnt, message, sizeof(message));

    // send(sock_clnt, message, sizeof(message), 0);

    close (sock_clnt);
    close (sock_serv);

    return 0;
}

void error_handling (const char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}