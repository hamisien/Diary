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

    FILE* fd = fopen("download_file.c", "w");
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

    /* while(1) {
        readnum = read(sd, buf, BUF_SIZE);
        //  printf("readnum = %d\n", readnum);
        //  printf("Received string data: %s\n", buf);

        if(readnum < BUF_SIZE) {
            fwrite(buf, sizeof(char), readnum, fd);
            break;
        } else {
            fwrite(buf, sizeof(char), readnum, fd);
        }
    } */ // 내가한거

    while((readnum = read(sd, buf, BUF_SIZE)) != 0) {
            fwrite(buf, sizeof(char), readnum, fd);
    }

    char thankyouarr[] = "Thank you for sending EOF!!";
    write(sd, thankyouarr, sizeof(thankyouarr));

    /* 
        char* thankyou = "Thank you for sending EOF!!"; 
        sizeof 함수의 인자에 포인터 변수를 넘겨주면 포인터가 가리키는 내용의 size를 반환하지 않고
        해당 포인터 변수의 사이즈를 반환한다.
        32비트 컴퓨터에서 포인터 변수의 크기는 4바이트, 64비트는 8바이트이다.
    */

    /* if(read(sd, buf, BUF_SIZE) == 0) {
        // printf("sizeof(char* thankyou): %d\n sizeof(char thankyou[]): %d\n", sizeof(thankyou), sizeof(thankyouarr));
        
    } */

    // fclose();
    fclose(fd);
    close(sd);

    return 0;
}

void error_handling(char* msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);

    exit(1);
}