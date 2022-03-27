#include <stdio.h>

int main()
{
    int num1;
    int num2;
    int i;

    scanf("%d %d", &num1, &num2);
    
    i = num1;

    while (1)
    {
		if(num1>200 || num1<1 || num2<10 || num2>200)
			break;
		if(i > num2)
			break;

		if(i % 10 == 7){
			i++;
			continue;
		}

        printf("%d ", i);
        i++;
    }

    return 0;
}
