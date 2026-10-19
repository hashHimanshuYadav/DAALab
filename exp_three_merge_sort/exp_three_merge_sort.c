#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxArrSize 100000


int merge_sort(int n, int arr[], int arrLen, int *resultsArr) {
	// Write code here
	if (n == 1) {
		resultsArr[0] = arr[0];
		return 1;
	}

	int mid = n / 2;

	// Sort left half into resultsArr[0 ... mid-1]
	// and right half into resultsArr[mid ... n-1]
	merge_sort(mid, arr, mid, resultsArr);
	merge_sort(n - mid, arr + mid, n - mid, resultsArr + mid);

	// Copy the two sorted halves back into arr temporarily so we can merge into resultsArr
	for (int i = 0; i < n; i++) {
		arr[i] = resultsArr[i];
	}

	// Merge the two halves from arr into resultsArr
	int i = 0, j = mid, k = 0;
	while (i < mid && j < n) {
		if (arr[i] <= arr[j]) {
			resultsArr[k++] = arr[i++];
		} else {
			resultsArr[k++] = arr[j++];
		}
	}

	while (i < mid) {
		resultsArr[k++] = arr[i++];
	}

	while (j < n) {
		resultsArr[k++] = arr[j++];
	}

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
	int resultsArrLength = merge_sort(n, arr, arrLen, resultsArr);
	printArrayElements(resultsArr, resultsArrLength);
	return 0;
}

// gcc exp_three_merge_sort.c -o output
// ./output 6 29,10,-14,-37,12,-5 
// o/p:- -37,-14,-5,10,12,29