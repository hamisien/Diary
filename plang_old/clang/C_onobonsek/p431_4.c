#include <stdio.h>
int main(void)
{
    int array[2][3]={10, 20, 30, 40, 50, 60};
    int (*p)[3]; //배열 포인터 변수의 선언부

    p = array; //배열 포인터 변수의 초기화
    printf("%d %d %d \n", p[0][0], p[0][1], p[0][2]);
    printf("%d %d %d \n", p[1][0], p[1][1], p[1][2]);

    return 0;
}