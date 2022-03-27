#include <stdio.h>

int main(void)
{
	int i=0;
	
	scanf("%d", &i);

	while(i!=1){
		i--;
		printf("%d\n", i);
	}
	printf("0");

	return 0;
}
