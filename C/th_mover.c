#include <stdio.h>
#include <memory.h>
#define MAX_LENGHT 255

void delete_nl(char* _buff);

int main(void)
{
    char f_buff[MAX_LENGHT] = {0, };
    char f_name[MAX_LENGHT] = "playlist.txt";
    char cmd_buff[MAX_LENGHT] = {0, };

    FILE* fp = fopen(f_name, "r");

    if (fp == NULL) {
                        printf("%s 파일을 여는 데 실패함", f_name);
                        return 1;
                    }
    else {
                        printf("%s 파일을 여는 데 성공함", f_name);
                    }

    while (fgets(f_buff, sizeof(f_buff), fp) != NULL) {
                            
                        delete_nl(f_buff);
                            
                        sprintf(cmd_buff, "sudo cp \"%s\" mv_tmp/", f_buff);
                        printf(cmd_buff);
                            
                        system(cmd_buff);
                            
                        memset(f_buff, 0, sizeof(f_buff));
                        memset(cmd_buff, 0, sizeof(cmd_buff));
                    }

    fclose(fp);

    return 0;
}

void delete_nl(char* _buff)
{
    _buff[strlen(_buff)-1] = '\0';

    return;
}