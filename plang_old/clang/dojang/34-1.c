#include <stdio.h>

int main()
{
	int *numPtr;
	printf("%d %d %d %d\n", sizeof(char *), sizeof(short*), sizeof(int*), sizeof(long*));
	printf("%d", sizeof(numPtr));

	return 0;
}
