#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxArrSize 100000


int find_min_max(int n, int arr[], int arrLen, int *resultsArr) {
	// Write code here
	if (n == 1) {
		resultsArr[0] = arr[0];
		resultsArr[1] = arr[0];
		return 2;
	}

	int mid = n / 2;
	int leftRes[2], rightRes[2];

	find_min_max(mid, arr, mid, leftRes);
	find_min_max(n - mid, arr + mid, n - mid, rightRes);

	resultsArr[0] = (leftRes[0] < rightRes[0]) ? leftRes[0] : rightRes[0];
	resultsArr[1] = (leftRes[1] > rightRes[1]) ? leftRes[1] : rightRes[1];

	return 2;
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
	int resultsArrLength = find_min_max(n, arr, arrLen, resultsArr);
	printArrayElements(resultsArr, resultsArrLength);
	return 0;
}
// gcc exp_two_max_min_dq.c -o output
// ./output 6 29,10,-14,-37,12,-5  