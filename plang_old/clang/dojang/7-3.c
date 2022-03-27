#include <stdio.h>

int main(void)
{
	char a;
	short b;
	int c;
	long d;
	long long e;

	printf("%d %d %d %ld %lld", sizeof a, sizeof b, sizeof c, sizeof d, sizeof e);
	
	return 0;
}
