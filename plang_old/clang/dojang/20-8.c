#include <stdio.h>

int main()
{
	char cha;

	scanf("%c", &cha);

	if(cha != 'k')
		printf("참\n");
	else
		printf("거짓\n");
	if(cha > 'h')
		printf("참\n");
	else
		printf("거짓\n");
	if(cha <= 'o')
		printf("참\n");
	else
		printf("거짓\n");

	return 0;
}
