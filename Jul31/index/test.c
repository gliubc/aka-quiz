#include <stdio.h>

#define N 10

int main(void)
{
	int arr[N] = {-1, 5, 7, 0, -22, 7, 8, -2, 0, 5};
	int i, sum, max; 

	i = sum = max = 0;
	while (i < N) {
		if (arr[i] > 0) {
			sum += arr[i];
			if (max < sum) 
				max = sum;
		} else {
			if (sum + arr[i] > 0) 
				sum += arr[i];
			else
				sum = 0;
		}
		++i;
	}
	printf("%d", max);
	return 0;
}
