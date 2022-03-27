#include <stdio.h>
#include <limits.h>

int main(void)
{
	int a = -2147483648;

	printf("%d", CHAR_MIN);
	printf("%d", UCHAR_MAX + 1);

	return 0;
}
