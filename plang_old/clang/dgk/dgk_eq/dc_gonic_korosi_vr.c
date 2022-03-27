#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 255

char gonic[50] = { 0, }, gid[50] = { 0, };

void gonic_korosi(char* _gid, char* _gonic, int cid, int _vnum);
int multiChk(int n, char* _gid, int* _cid);

int main(void)
{
	char inputVal = 0;
	int vnum = 0, crit_pid = 0; //crit_pid = cid


	printf("특정한 고닉 사용자 게시글 조회수를 증폭시키는 프로그램\n\n");
	printf("시작하려면 아무 키나 누르세요.\n");
	getchar();
	
GET_INFO:
	system("clear");
	printf("갤러리 ID를 입력하세요: ");
	scanf("%s", gid);
	getchar();

	printf("고닉 아이디를 입력하세요: ");
	scanf("%s", gonic);
	getchar();

GET_CRIT_PID:
	printf("기준 게시글 ID를 입력하세요: ");
	scanf("%d", &crit_pid);

GET_VNUM:
	printf("증가시킬 조회수를 입력하세요: ");
	scanf("%d", &vnum);
	getchar();

	while(1){
		system("clear");
		printf("GID: %s\nID: %s\nCID: %d\nVNUM: %d\n\n위 정보가 맞습니까?(Y/N): ", gid, gonic, crit_pid, vnum);
		scanf("%c", &inputVal);
		getchar();

		if(inputVal == 'Y' | inputVal == 'y'){ gonic_korosi(gid, gonic, crit_pid, vnum);
			/* switch(gonic_korosi(gid, gonic, crit_pid, vnum)){
				case 1: 
					goto GET_INFO; break;
				case 2:
					goto GET_VNUM; system("clear"); break;
				case 9:
					continue;
				case 0:
					return 0;
				default:
					printf("제시된 값만 입력하세요!\n");
					getchar(); */
				break;
			}
		else if(inputVal == 'N' | inputVal == 'n') goto GET_INFO;
		else {
			printf("Y 또는 N을 입력하세요.\n\n");
			getchar();
		}
	}

	return 0;
}

void gonic_korosi(char* _gid, char* _gonic, int cid, int _vnum)
{
	char cmd_buff[MAX_LENGTH] = {0,}, buff[MAX_LENGTH] = {0,}, nocid_flag = 0, err_first_try = 1;
	char* strsearch = NULL;
	unsigned int retry_counter = 1;
	int i = 0;
	char trigger_p[50] = "브갤좋아", trigger_n[50] = "브갤싫어", trigger_l[50] = "브갤사랑해";
	
	system("clear");
	printf("아무 키나 누르면 시작합니다!\n");
	getchar();

	while(1) { // CID를 기준으로 게시글 넘버를 1씩 올려가며 해당 고닉이 있는지를 탐색. 있으면 조회수 증폭, 없으면 1 증가. 게시글이 존재하지 않으면 대기
		system("clear");
		printf("게시글 %d의 분류를 시작합니다.\n", cid);
		printf("대상 갤러리: %s\n대상 고닉: %s\n", _gid, gonic);
		system("sleep 0.3");
NO_CID:
		memset(buff, 0, sizeof(buff));
		memset(cmd_buff, 0, sizeof(cmd_buff));
		sprintf(cmd_buff, "curl -s -L m.dcinside.com/board/%s/%d > buffer", _gid, cid); /* | grep -i \"derror/deleted\" */ /* -A \"Mozilla/5.0 (iPhone; CPU iPhone OS 6_1_3 like Mac OS X) AppleWebKit/536.26 (KHTML, like Gecko) CriOS/28.0.1500.12 Mobile/10B329 Safari/8536.25\" */
		// 위에 코드를 "wget -O buffer https://m.dcinside.com/board/%s/%d" 로 대체 가능함. 원본: "curl -s -L m.dcinside.com/board/%s/%d > buffer"
		system(cmd_buff);

		FILE *fp = fopen("buffer", "r");

		char pinyong_flag = 0; // 0이면 없음, 1은 사랑해, 2는 싫어

		while(fgets(buff, sizeof(buff), fp) != NULL){
			//printf("%s\n", buff);
			//system("sleep 0.01");
			if (strsearch = strstr(buff, trigger_p) != NULL) pinyong_flag = 1; // 대상 고닉 제외 키워드
			else if (strsearch = strstr(buff, trigger_n) != NULL) pinyong_flag = 2; // 대상 고닉 변경 키워드
			else if (strsearch = strstr(buff, trigger_l) != NULL) pinyong_flag = 3; // 대상 고닉을 전체로 설정 키워드
			if (strsearch = strstr(buff, "gallview_contents")) {
				system("sleep 0.2");
				retry_counter = 1;
				nocid_flag = 0;
				break;
			}
			else if (strsearch = strstr(buff, "derror/deleted") != NULL){
				// 등록되지 않은 게시글이면 스탠바이
				// printf("스탠바이 대상입니다.\n");
				// system("clear");
				// strsearch = strstr(buff, "derror/deleted");
				if(err_first_try = 1)
					if (multiChk(2, gid, &cid) == 1) { //gonic_korosi(gid, gonic, crit_pid, vnum);
						nocid_flag = 0;
						break;
					}
					else err_first_try = 0;

				printf("\n게시글 %d이(가) 존재하지 않습니다.\n", cid);
				printf("해당 게시글이 작성될 때까지 기다리는 중 ... (%d)\n\n", retry_counter);
				// printf("strsearch 값: %s\n", strsearch); //← 이 코드 왜인지 모르겠지만 오류 발생함. (core dumped)

				nocid_flag = 1;
				break;
			}
			else if (strsearch = strstr(buff, "ID 입력\" class=\"intxt\" value=\"") != NULL) {
				// strsearch = strstr(buff, "ID 입력\" class=\"intxt\" value=\"");
				if (pinyong_flag == 3) { // 만약 어떤 고닉이 "피뇽이싫어" 키워드를 입력했다면 대상 고닉을 우선으로.
					printf("\n게시글 %d에서 \"%s\" 키워드가 감지되었습니다.\n대상 고닉을 전체(\")로 변경합니다.\a\n\n", cid, trigger_l);
					system("sleep 1");
					// printf("현재 gonic의 값: %s\n", gonic);
					// system("sleep 1");
					memset(gonic, 0, sizeof(gonic)); 
					// 위에 memset 함수로 포인터 변수인 _gonic을 초기화하면 segmentation fault 오류가 난다.
					// 이유는 _gonic은 포인터 변수로, 메모리 주소를 저장하는 변수이기 때문이다.
					// 참고로 포인터 변수의 크기(sizeof(포인터변수))는 8바이트다.
					// printf("memset한 gonic의 값: %s\n", gonic);
					// system("sleep 1");
					strcpy(gonic, "\"");

					system("clear");
					printf("게시글 %d의 분류를 시작합니다.\n", cid);
					printf("대상 갤러리: %s\n대상 고닉: %s\n", _gid, gonic);
					printf("\n게시글 %d에서 \"%s\" 키워드가 감지되었습니다.\n대상 고닉을 전체(\")로 변경합니다.\a\n\n", cid, trigger_l);
					printf("수정된 대상 고닉: %s\a\n", gonic);
					system("sleep 2");

					_vnum = 100;

					for(i=0; i<_vnum/2; i++){
						system("clear");
						printf("대상 고닉: %s\n\n", gonic);
						printf("게시글 %d: %d\n", cid, 2*i+2);
						sprintf(cmd_buff, "wget -q -o /dev/null -O /dev/null https://m.dcinside.com/board/%s/%d &", _gid, cid);
						system(cmd_buff);
					}

					nocid_flag = 0;
					sprintf(cmd_buff, "mkdir -p b.archive/%s && cd b.archive/%s && wget -q -o /dev/null https://m.dcinside.com/board/%s/%d &", _gid, _gid, _gid, cid);
					system(cmd_buff);
					printf("\n");
					system("sleep 1");
					break;
				}
				if (pinyong_flag == 2) { // 만약 어떤 고닉이 "피뇽이싫어" 키워드를 입력했다면 대상 고닉을 우선으로.
					printf("\n게시글 %d에서 \"%s\" 키워드가 감지되었습니다.\n대상 고닉을 변경합니다.\a\n\n", cid, trigger_n);
					system("sleep 1");
					// printf("현재 gonic의 값: %s\n", gonic);
					// system("sleep 1");
					memset(gonic, 0, sizeof(gonic)); 
					// 위에 memset 함수로 포인터 변수인 _gonic을 초기화하면 segmentation fault 오류가 난다.
					// 이유는 _gonic은 포인터 변수로, 메모리 주소를 저장하는 변수이기 때문이다.
					// 참고로 포인터 변수의 크기(sizeof(포인터변수))는 8바이트다.
					// printf("memset한 gonic의 값: %s\n", gonic);
					// system("sleep 1");
					int i;
					for (i = 77; buff[i] != '\"'; i++){
						gonic[i-77] = buff[i];
						system("sleep 0.1");
						system("clear");
						printf("게시글 %d의 분류를 시작합니다.\n", cid);
						printf("대상 갤러리: %s\n대상 고닉: %s\n", _gid, gonic);	
						printf("\n게시글 %d에서 \"%s\" 키워드가 감지되었습니다.\n대상 고닉을 변경합니다.\a\n\n", cid, trigger_n);
						printf("수정된 대상 고닉: %s\a\n", gonic);
						/*
						printf("_gonic: %c\nbuff: %c\n", _gonic[i-77], buff[i]);
						printf("수정된 _gonic: %s\n", _gonic);
						printf("i = %d\n\n", i);
						system("sleep 0.5");
						*/
					} gonic[i-77] = '\0';

					system("clear");
					printf("게시글 %d의 분류를 시작합니다.\n", cid);
					printf("대상 갤러리: %s\n대상 고닉: %s\n", _gid, gonic);
					printf("\n게시글 %d에서 \"%s\" 키워드가 감지되었습니다.\n대상 고닉을 변경합니다.\a\n\n", cid, trigger_n);
					printf("수정된 대상 고닉: %s\a\n", gonic);
					system("sleep 1");

					_vnum = 1000;

					for(i=0; i<_vnum/2; i++){
						system("clear");
						printf("대상 고닉: %s\n\n", gonic);
						printf("게시글 %d: %d\n", cid, 2*i+2);
						sprintf(cmd_buff, "wget -q -o /dev/null -O /dev/null https://m.dcinside.com/board/%s/%d &", _gid, cid);
						system(cmd_buff);
					}

					nocid_flag = 0;
					sprintf(cmd_buff, "mkdir -p b.archive/%s && cd b.archive/%s && wget -q -o /dev/null https://m.dcinside.com/board/%s/%d &", _gid, _gid, _gid, cid);
					system(cmd_buff);
					printf("\n");
					system("sleep 1");
					break;
				}
				else if (strsearch = strstr(buff, gonic) != NULL){
					if (pinyong_flag == 1) {
						printf("\n게시글 %d에서 \"%s\" 키워드가 감지되었습니다.\n대상 고닉을 제외합니다.\a\n", cid, trigger_p);
						system("sleep 1");
						// printf("현재 gonic의 값: %s\n", gonic);
						// system("sleep 1");
						memset(gonic, 0, sizeof(gonic));
						// printf("memset한 gonic의 값: %s\n", gonic);
						// system("sleep 1");
						strcpy(gonic, "(없​​​​​​​​​​음)");
						/*
						2020-11-18 "피뇽이사랑해"에서 Segmentation fault 오류가 계속 났던 이유는 
						이미 선언된 배열(및 그 배열을 가리키는 포인터)에 문자열을 할당하려고 했기 때문이다.
						*/
						// printf("strcpy로 (없음)을 넣은 뒤의 값: %s\n", gonic);
						// system("sleep 1");
						nocid_flag = 0;
						sprintf(cmd_buff, "mkdir -p b.archive/%s && cd b.archive/%s && wget -q -o /dev/null https://m.dcinside.com/board/%s/%d &", _gid, _gid, _gid, cid);
						system(cmd_buff);
						//sprintf(cmd_buff, "pwd"); // 위 cd 명령어를 실행하여 경로를 바꿔도 초기 쉘 실행 경로가 유지되는지 확인
						//system(cmd_buff);
						break;
					}

					// 해당 고닉을 찾으면 조회수 증폭
					// strsearch = strstr(buff, _gonic);
					strsearch = strstr(buff, gonic);
					// printf("%s", strsearch);
					printf("\n고닉 찾음: %s\a\a\n", gonic); //96번째 줄에서 오류가 났던 이유는 if 인자에서 대입을 했기 때문인 것 같음.
					system("sleep 0.5");

					for(i=0; i<_vnum/2; i++){
						system("clear");
						printf("대상 고닉: %s\n\n", gonic);
						printf("게시글 %d: %d\n", cid, 2*i+2); //C컴파일러는 기본적으로 우에서 좌로 인식하기에 괄호와 같은 우선연산기호가 없어도 된다.
						sprintf(cmd_buff, "wget -q -o /dev/null -O /dev/null https://m.dcinside.com/board/%s/%d &", _gid, cid);
						// -q 옵션은 wget 아웃풋을 간소화, -o 옵션은 wget 로그 파일 위치, -O 옵션은 다운로드 받은 웹 파일의 위치
						// 위 코드를 "wget -q -O /dev/null https://m.dcinside.com/board/%s/%d &"로 대체 가능함. 원본: "curl -k -l -o /dev/null -s -L m.dcinside.com/board/%s/%d & >&-"
						system(cmd_buff);
					}
					nocid_flag = 0;
					break;
				}
			}
		}
		fclose(fp);

		if(nocid_flag == 1){
			system("sleep 2");
			retry_counter++;
		}
		else if(nocid_flag == 0) {
			cid++;
			retry_counter = 1;
			err_first_try = 1;
		}
	}

/* RE:
	system("clear");
	printf("%s, %s, %d", _gid, _gonic, _vnum);

	printf("\n\n작업이 종료되었습니다.\n");
	printf("1. 모든 정보를 다시 입력하기\n");
	printf("2. 조회수만 다시 입력하기\n");
	printf("9. 방금 실행한 작업은 다시 실행하기\n");
	printf("0. 프로그램을 종료하기\n");

	int val = 0;
	scanf("%d", &val);
	getchar();
	if(val == 9) goto RE; */
}

int multiChk(int n, char* _gid, int* _cid)
/*
중간에 삭제된 글을 탐지하고 패스하기 위해 상위의 글을 N번 체크하는 함수.
*/
{
	char cmd_buff[MAX_LENGTH] = {0,}, buff[MAX_LENGTH] = {0,};
	char* strsearch = NULL;
	int flag = 0, i;

	for(i = 1; i <= n && flag == 0; i++) {
		memset(buff, 0, sizeof(buff));
		memset(cmd_buff, 0, sizeof(cmd_buff));
		sprintf(cmd_buff, "curl -s -L m.dcinside.com/board/%s/%d > multi", _gid, *_cid + i);
		system(cmd_buff);

		FILE *fp = fopen("multi", "r");

		while(fgets(buff, sizeof(buff), fp) != NULL)
			if (strsearch = strstr(buff, "content-language") != NULL) {
				flag = 1;
				*_cid += (i-1);
				break;
			}

		fclose(fp);
	}

	return flag?1:0;
}
