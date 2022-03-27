#include <stdio.h>

struct space //구조체 정의.. 구조체 안에서 변수를 선언과 동시에 정의하면, main 함수에서 구조체 변수를 선언과 동시에 정의했을 때 오류가 발생한다.
{
    int alpha;
    int beta;
    int ceta;
    int delta;
};

int main(void)
{
    struct space s = {1, 2, 3, 4}; //구조체 변수 선언과 정의
    struct space s2 = {9, 8, 7, 6};

    printf("%d %d %d %d\n", s.alpha, s.beta, s.ceta, s.delta);

    s = s2;

    printf("%d %d %d %d\n", s.alpha, s.beta, s.ceta, s.delta);

    return 0;
}