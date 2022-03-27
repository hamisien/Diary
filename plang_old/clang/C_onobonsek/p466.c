#include <stdio.h>

void shiftone(char *p);

int main(void)
{
	int i;
	char arr[8]={1, 2, 3, 4, 5, 6, 7, 8};

	printf("실행 전 : ");
	for(i=0;i<8;i++){
		printf("%d ", arr[i]);
	}

	shiftone(arr);

	printf("\n실행 후 : ");
	for(i=0;i<8;i++){
		printf("%d ", arr[i]);
	}

	return 0;
}

void shiftone(char *p)
{
	int j;
	char tmp = 0;

	for(j=0;j<8;j++){
		if(j=7){
			p[0] = p[j];
			p[j] = p[j-1];
			break;
		}
		///*
		tmp = p[j+1];
		p[j+1] = p[j];
		p[j+2] = tmp;
		//*/
	}
}
