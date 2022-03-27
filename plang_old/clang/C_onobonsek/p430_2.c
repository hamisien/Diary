#include <stdio.h>
int main(void)
{
    int array[5]={10, 20, 30, 40, 50};
    int *p; //1포인터 변수의 선언부

    p = array; //2 포인터 변수의 초기화
    printf("%d %d %d %d %d \n", p[0], p[1], p[2], p[3], p[4]);
    printf("%d %d %d %d %d \n", *(p+0), *(p+1), *(p+2), *(p+3), *(p+4));

    return 0;
}