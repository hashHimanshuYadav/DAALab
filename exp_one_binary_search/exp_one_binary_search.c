#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binary_search(int n, int arr[], int arrLen, int target) {
	// Write code here
	int low = 0, high = n - 1;
	int result = -1;

	while (low <= high) {
		int mid = low + (high - low) / 2;

		if (arr[mid] == target) {
			result = mid;
			high = mid - 1;
		} else if (arr[mid] < target) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}

	return result;
}


int readIntArray(char *argsArray, int arr[]) {
	int col = 0;
	char *token = strtok(argsArray, ",");
	while (token != NULL) {
		arr[col] = atoi(token);
		token = strtok(NULL, ",");
		col++;
	}
	return col;
}

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
	int arr[strlen(argv[2])];
	int target = atoi(argv[3]);
	int arrLen = readIntArray(argv[2], arr);
	printf("%d\n", binary_search(n, arr, arrLen, target));
	return 0;
}

// gcc exp_one_binary_search.c -o output
// ./output 8 10,20,30,40,40,50,60,70 40