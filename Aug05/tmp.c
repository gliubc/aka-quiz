#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_arr(int *arr, int len)
{

	int i, j, ran;

	srand(time(NULL));
	for (i = 0; i < len; ++i) {
again:
		ran = rand() % 50;
		for (j = 0; j < i; ++j) {
			if (ran == arr[j]) {
				goto again;
			}
		}
		arr[i] = ran;
	}
}

void print_arr(int *arr, int len)
{
	int i;
	int arr[10] = {0};
	
	for (i = 0; i < len; ++i) {
		printf("%d ", arr[i]);
	}
}

void quick_sort(int *arr, int left, int right)
{
	int first, l, r;

	if (left >= right) {
		return;
	}

	first = arr[left];
	l = left;
	r = right;

	while (l < r) {
		while (l < r && arr[r] >= first) {
			--r;
		}		
		arr[l] = arr[r];

		while (l < r && arr[l] <= first) {
			++l;
		}
		arr[r] = arr[l];
	}
	arr[l] = first;

	quick_sort(arr, left, l);
	quick_sort(arr, l+1, right);
}

void sort_arr(int *arr, int len)
{
	quick_sort(arr, 0, len-1);	
}

int main(void)
{
	int arr[20];

	init_arr(arr, 20);
	print_arr(arr, 20);
	sort_arr(arr, 20);
	print_arr(arr, 20);
	
	return 0;
}
