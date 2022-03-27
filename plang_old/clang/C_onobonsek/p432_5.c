#include <stdio.h>
int main(void)
{
    char *string[2]={"I Love C", "Hello World"};

    printf("%s %s\n", string[0], string[1]+6);
    printf("The value of 3rd argument is %d\n\a", *(string[1]+6));
    printf("정수 %d은 ASCII 코드표에서 %c입니다.\n", *(string[1]+6), 87);

    return 0;
}