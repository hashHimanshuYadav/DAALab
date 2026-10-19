#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxArrSize 100000


int quick_sort(int n, int arr[], int arrLen, int *resultsArr) {
	// Write code here
	if (n <= 0) {
		return 0;
	}
	if (n == 1) {
		resultsArr[0] = arr[0];
		return 1;
	}

	int pivot = arr[0];
	int i = 0;

	// Partition using the first element as pivot
	for (int j = 1; j < n; j++) {
		if (arr[j] <= pivot) {
			i++;
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

	// Place the pivot in its correct sorted position at index i
	int temp = arr[0];
	arr[0] = arr[i];
	arr[i] = temp;

	// Store the pivot in resultsArr and recursively sort the left and right subarrays
	resultsArr[i] = arr[i];
	quick_sort(i, arr, i, resultsArr);
	quick_sort(n - i - 1, arr + i + 1, n - i - 1, resultsArr + i + 1);

	return n;
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

void printArrayElements(int *resultsArr, int resultsArrLength) {
	int index;
	for(index = 0; index < resultsArrLength - 1; index++) {
		printf("%d,", resultsArr[index]);
	}
	printf("%d\n", resultsArr[index]);
}

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
	int arr[strlen(argv[2])];
	int arrLen = readIntArray(argv[2], arr);
	int resultsArr[MaxArrSize];
	int resultsArrLength = quick_sort(n, arr, arrLen, resultsArr);
	printArrayElements(resultsArr, resultsArrLength);
	return 0;
}
// gcc exp_four_quick_sort.c -o output
// ./output 6 29,10,-14,-37,12,-5     
// o/p:- -37,-14,-5,10,12,29