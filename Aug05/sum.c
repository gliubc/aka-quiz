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

	for (i = 0; i < len; ++i) {
		printf("%d:%d ", i, arr[i]);
		(i+1) % 10 == 0 ? putchar('\n') : 0;
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

int half_search(int *arr, int len)
{
	int k, l, r, m;

	k = 40;
	l = 0;
	r = len - 1;

	while (l < r) {
		m = (l + r) / 2;
		if (arr[m] == k) {
			return m;
		} else if (arr[m] > k) {
			r = m;
		} else {
			l = m + 1;
		}
	}
	return l-1;
}

int main(void)
{
	int arr[20], l, r;

	init_arr(arr, 20);
	//print_arr(arr, 20);
	sort_arr(arr, 20);
	print_arr(arr, 20);

	l = 0;
	if (arr[l] >= 40) {
		return 0;
	}
	r = half_search(arr, 20);
	printf("%d\n", r);

	while (l <= r) {
		if (arr[l] + arr[r] == 40) {
			printf("%d, %d\n", l, r);
			++l;
			--r;
		} else if (arr[l] + arr[r] < 40) {
			++l;
		} else {
			--r;
		}
	}
	return 0;
}
