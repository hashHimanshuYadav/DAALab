#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxArrSize 100000


int heap_sort(int n, int arr[], int arrLen, int *resultsArr) {
	// Write code here
	// Step 1: Copy elements into resultsArr
	for (int i = 0; i < n; i++) {
		resultsArr[i] = arr[i];
	}

	// Step 2: Build a Max Heap
	for (int i = n / 2 - 1; i >= 0; i--) {
		int parent = i;
		while (2 * parent + 1 < n) {
			int left = 2 * parent + 1;
			int right = 2 * parent + 2;
			int largest = parent;

			if (left < n && resultsArr[left] > resultsArr[largest]) {
				largest = left;
			}
			if (right < n && resultsArr[right] > resultsArr[largest]) {
				largest = right;
			}
			if (largest != parent) {
				int temp = resultsArr[parent];
				resultsArr[parent] = resultsArr[largest];
				resultsArr[largest] = temp;
				parent = largest;
			} else {
				break;
			}
		}
	}

	// Step 3: Extract elements from the Max Heap one by one
	for (int i = n - 1; i > 0; i--) {
		// Move current root (maximum) to the end
		int temp = resultsArr[0];
		resultsArr[0] = resultsArr[i];
		resultsArr[i] = temp;

		// Max-heapify the reduced heap of size i
		int parent = 0;
		while (2 * parent + 1 < i) {
			int left = 2 * parent + 1;
			int right = 2 * parent + 2;
			int largest = parent;

			if (left < i && resultsArr[left] > resultsArr[largest]) {
				largest = left;
			}
			if (right < i && resultsArr[right] > resultsArr[largest]) {
				largest = right;
			}
			if (largest != parent) {
				int swap = resultsArr[parent];
				resultsArr[parent] = resultsArr[largest];
				resultsArr[largest] = swap;
				parent = largest;
			} else {
				break;
			}
		}
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
	int resultsArrLength = heap_sort(n, arr, arrLen, resultsArr);
	printArrayElements(resultsArr, resultsArrLength);
	return 0;
}

// gcc exp_five_heap_sort.c -o output                          
// ./output 6 29,10,-14,-37,12,-5   
// o/p:- -37,-14,-5,10,12,29                                    