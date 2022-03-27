#include <stdio.h>

int main()
{
	int a, b;
	
	scanf("%d %d", &a, &b);

	printf("%s\n", a&&b ? "참" : "거짓");
	printf("%s\n", a||b ? "참" : "거짓");
	printf("%s\n", !a ? "참" : "거짓");

	return 0;
}
