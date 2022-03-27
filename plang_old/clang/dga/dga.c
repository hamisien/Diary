#include <stdio.h>
#include <string.h>
#define MAXLENGHT 255

void getVal(char *gid, int *cid, int *now);
void valIndicator(char *gid, int *cid, int *now);
void runArchive(char *gid, int *cid, int *now);

int main(void)
{
    char gid[MAXLENGHT] ={ 0, };
    int cid, now;
    char answ = 0;

	system("clear");
    puts("<<< DCinside Gallery Archive >>>\n");
    printf("Press any key to continue..");
    getchar();

GET_INFO:
    cid = 0;
    now = 0;
    memset(gid, 0, sizeof(gid)); // 재입력을 고려한 변수 초기화
    getVal(gid, &cid, &now); // gid와 cid를 입력 받음

    now = cid; // now의 초기화
    getchar();
    
ANSW:
    system("clear");
    valIndicator(gid, &cid, &now); // 입력받은 값을 표시&확인
    printf("Is the above info correct? (Y/N): ");
    scanf("%c", &answ); // Y 또는 N을 입력 받음
    //putc(answ, stdout);

    if(answ == 'Y' | answ == 'y') runArchive();
    else if(answ == 'N' | answ == 'n') goto GET_INFO;
    else {
        printf("Input Y or N.\n");
        getchar();
        getchar();
        goto ANSW;
    }

    return 0;
}

void getVal(char *gid, int *cid, int *now)
{
    char tmp_gid[MAXLENGHT] = {0,};

    system("clear");
    valIndicator(gid, cid, now);
    printf("Gallery : ");
    memset(gid,0,sizeof(gid));
    scanf("%s", tmp_gid);
    strcpy(gid, tmp_gid);
    system("clear");
    valIndicator(gid, cid, now);
    printf("Criteria: ");
    scanf("%d", cid);

    return;
}

void valIndicator(char *gid, int *cid, int *now)
{
    printf("┌");
    for(int i=0;i<30;i++)
        printf("─");
    puts("┐");

    printf("│%-10s: %-18s│\n", " Gallery", gid);
        
    printf("├");
    for(int i=0;i<30;i++)
        printf("─");
    puts("┤");
    
	if(*cid==0) printf("│%-10s: %-18c│\n", " Criteria", ' ');
	else printf("│%-10s: %-18d│\n", " Criteria", *cid);

    printf("├");
    for(int i=0;i<30;i++)
        printf("─");
    puts("┤");

	if(*now==0) printf("│%-10s: %-18c│\n", " Current", ' ');
	else printf("│%-10s: %-18d│\n", " Current", *now);

    printf("└");
    for(int i=0;i<30;i++)
        printf("─");
    puts("┘");

    return;
}

void runArchive(char *gid, int *cid, int *now)
{
    char cmd_buff[MAX_LENGTH] = {0,}, buff[MAX_LENGTH] = {0,}, nocid_flag = 0;
    // buffer 뒤에 rand 함수를 이용하여 난수 추가

    while(1){
        memset(buff, 0, sizeof(buff));
		memset(cmd_buff, 0, sizeof(cmd_buff));
        sprintf(cmd_buff, "curl -A \"Mozilla/5.0 (Linux; Android 10; Pixel 4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4280.141 Mobile Safari/537.36\" -L m.dcinside.com/board/%s/%d > buffer", gid, *now);
		system(cmd_buff);

		FILE *fp = fopen("buffer", "r");

		while(fgets(buff, sizeof(buff), fp) != NULL){
            if (strsearch = strstr(buff, "derror/deleted") != NULL){
            }
        }

        system("clear");
        valIndicator(gid, cid, now);
    }

    return;
}
