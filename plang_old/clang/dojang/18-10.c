#include <stdio.h>

int main()
{
    char k, e, m, s;
    int avg = 0;
    
    scanf("%d %d %d %d", &k, &e, &m, &s);
    if(k>=0&&k<=100&&e>=0&&e<=100&&m>=0&&m<=100&&s>=0&&s<=100){
        avg = (k+e+m+s)/4;
        if(avg >= 85)
            printf("합격");
        else
            printf("불합격");
    }
    else
        printf("잘못된 점수");
        
    return 0;
}
