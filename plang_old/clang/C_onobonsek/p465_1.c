#include <stdio.h>

void func(char a, void* b, int c, double d);

int main(void)
{
	char c='A';
	char* str="ABCD";
	int num1=10;
	double num2=3.14;

	func(c, str, num1, num2);
	return 0;
}

void func(char a, void* b, int c, double d)
{
	printf("%c %s %d %lf", a, b, c, d);
}
