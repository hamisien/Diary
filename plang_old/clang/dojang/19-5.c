#include <stdio.h>

int main()
{
	int balance = 10000;
	int age;

	scanf("%d", &age);

	if(age>=7 && age<=12)
		balance -= 450;
	else if(age>=13 && age<=18)
		balance -= 720;
	else if(age>=19)
		balance -= 1200;
	else
		printf("공짜입니다.");

	printf("%d\n", balance);

	return 0;
}
