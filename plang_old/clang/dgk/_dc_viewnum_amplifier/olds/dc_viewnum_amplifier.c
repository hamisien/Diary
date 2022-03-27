#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
//#include <ncurses.h>

//int system(const char *command); system 함수 이용하려면 이게 필요한 줄 알았는데 없애도 작동 잘됨.. 머지?

int main(void)
{
        int pid[10]={0}; //게시글 넘버
        char gid[30]={0}; //갤러리 ID
        int vnum=0, i; //각각 상승시킬 조회수 값, 카운터
        char cmd_buffer[100]={0};
        int sl;
        int goto_num=0;

        system("clear");

        printf("디시인사이드 조회수 올려주는 프로그램입니다.\n");
        printf("수능 11일 남았는데 이런 걸 만드네요. C언어도 다 까먹었는데 허허..\n");
        printf("요즘 태블릿에 SSH 연결하고 여러가지 하고 있네요. \n지금은 W3M이라는 텍스트기반 웹 브라우저로 디시인사이드 탐험하는 중..\n\n아무키나 누르면 시작합니다..");
        getchar(); //curses.h나 conio.h 등의 헤더파일은 gcc에서 문제가 있는 듯하다. 따라서 stdio.h에서 사용할 수 있는 getchar(); 등장!!
get_gid:
        system("clear");
        printf("갤러리 ID를 입력하세요: ");
        scanf("%s", &gid);
        printf("\n입력된 갤러리 ID: %s", gid);
get_pid:
        printf("\n\n다음으로, 게시글 넘버를 입력하세요: ");
        scanf("%ls", &pid);
        printf("\n입력된 게시글 넘버: %ls", pid);
get_vnum:
        printf("\n\n상승시킬 조회수 값을 입력하세요: ");
        scanf("%d", &vnum);
        printf("\n입력된 상승 조회수 값: %d", vnum);
        getchar(); //위의 scanf에서 값을 입력받고 아직 버퍼에 남아있는 입력값을 좌측의 getchar();가 비워준다!!
re:
        printf("\n\n시작하려면 아무 키나 누르세요!! >_<");
        getchar();

        for(i=0; i<vnum/2; i++){
                system("clear");
                printf("실행 횟수: %d\n", 2*i+2); //C컴파일러는 기본적으로 우에서 좌로 인식하기에 괄호와 같은 우선연산기호가 없어도 된다.
                sprintf(cmd_buffer, "curl -s -L m.dcinside.com/board/%s/%ls >&-", gid, pid); //-s 옵션은 --silent로, 무엇도 출력하지 않는다. 또한, >&-는 출력값을 &-(?)에 전달하여 출력하라는 것으로, >는 리디렉션 기호이다. &-에 대해선 좀더 알아보자. 첨엔wm3으로하려고했다가무리인거같아서wget으로하려했다가다운이돼서결국curl로하기로함.curl굿굿.
                system(cmd_buffer);
        }

        for(sl=0; sl<3; sl++){
        system("clear");
        system("sleep 0.5"); //sleep(0.5);
        printf("완료 >_< !!\n"); //sleep 사용할 때는 printf("aa"); 에서 aa 뒤에 '\n'가 들어가거나 fflush, getchar 등으로 버퍼 비워줘야 함.
        system("sleep 0.5"); //sleep(0.5);
        }

        printf("\n\n1. 갤러리 ID를 다시 입력하기\n2. 게시글 넘버를 다시 입력하기\n3. 상승시킬 조회수 값을 다시 입력하기\n9. 방금 실행한 명령을 다시 실행하기\n0. 프로그램을 종료하기\n\n입력: "); //왜인지는 모르겠으나, curl로 한번 페이지를 불러올 때마다 조회수가 2씩 올라간다. 따라서 입력받은 조회수 값을 2로 나누어 로드하도록 했고, 표시되는 값을 2배하여 정상적으로 보이도록 했다.
        scanf("%d", &goto_num);
        system("clear");

        switch(goto_num){
            case 1:
                goto get_gid;
            case 2:
                goto get_pid;
            case 3:
                goto get_vnum;
            case 9:
                goto re;
            case 0:
                break;
        }

    	/*sprintf(cmd_buffer, "w3m m.dcinside.com/board/%s/%ls", gid, pid);

        for(i=0; i<vnum; i++)
                system(cmd_buffer); //%s/%d", gid, pid);*/

        return 0;
}
