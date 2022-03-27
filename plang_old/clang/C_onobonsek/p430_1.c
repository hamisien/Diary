#include <stdio.h>
int main(void)
{
    int arr[] = {10, 30, 40, 30, 20};
    int *ap = arr;
    printf("%d\n", ap[0]+ap[1]+ap[2]+ap[3]);

    return 0;
}