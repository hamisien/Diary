#include <stdio.h>

int main()
{
	int cash;
	
	scanf("%d", &cash);

	while(cash>=1200){
		cash -= 1200;
		printf("%d\n", cash);
	}

	return 0;
}
