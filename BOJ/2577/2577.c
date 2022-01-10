#include <stdio.h>

int main(void)
{
	int input[3] = {0,};
	int result = 0;
	int count[10] = {0,};

	puts("A, B, C를 입력하세요.");

	for(int i = 0; i < 3; i++){
		scanf("%d", &input[i]);
		if (input[i] < 100 || input[i] >= 1000){
			puts("100 이상 1000 미만의 자연수만 입력하세요!");
			return 1;
		}
	}

	printf("A * B * C = %d\n", result = input[0]*input[1]*input[2]);

	for(int i = 0; result > 0; result /= 10){
		i = result%10;
		// printf("%d\n", i);
		for(int j = 0; j < 10; j++) {
			if (j == i)
				count[j]++;
		}
	}

	puts("\n\n결과는..");

	for (int i = 0; i < 10; i++) {
		printf("%d\n", count[i]);
	}

	return 0;
}
