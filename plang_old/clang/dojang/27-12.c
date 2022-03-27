#include <stdio.h>

int main()
{
	char ch;

	scanf("%c", &ch);
	
	for(;ch<='z';ch++)
		printf("%c", ch);

	return 0;
}
