#include <stdio.h>

void func(int *p, int (*p2)[2]);

int main(void)
{
	int array1[4]={10, 20, 30, 40};
	int array2[2][2]={50, 60, 70, 80};

	func(array1, array2);
	return 0;
}

void func(int *p, int (*p2)[2])
{
	int i, j;

	for(i=0; i<16/sizeof(int); i++){
		printf("%d ", p[i]);
	}

	printf("\n");

	for(i=0; 2; i++){
		for(j=0; 2; j++){
			printf("%d ", p2[i][j]);
		}
	}
	printf("끝");
}
