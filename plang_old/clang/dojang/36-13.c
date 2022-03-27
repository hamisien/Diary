#include <stdio.h>

int main()
{
    int numArr[5];
    int smallestNumber;

    scanf("%d %d %d %d %d", &numArr[0], &numArr[1], &numArr[2], &numArr[3], &numArr[4]);

	smallestNumber = numArr[0];

	for(int i = 0; i < (sizeof(numArr)/sizeof(int)-1); i++){
		if(smallestNumber > numArr[i+1])
			smallestNumber = numArr[i+1];
	}

    printf("%d\n", smallestNumber);

    return 0;
}
