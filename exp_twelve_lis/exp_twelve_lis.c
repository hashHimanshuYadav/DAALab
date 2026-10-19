#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lis(int n, int arr[], int arrLen) {
	int dp[1000];
	int i, j;
	int best = 0;

	// every element alone is an increasing subsequence of length 1
	for (i = 0; i < n; i++) {
		dp[i] = 1;
	}

	for (i = 1; i < n; i++) {
		for (j = 0; j < i; j++) {
			// arr[j] is smaller, so arr[i] can extend the subsequence ending at j
			if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
				dp[i] = dp[j] + 1;
			}
		}
	}

	// the answer is the biggest value in dp[]
	for (i = 0; i < n; i++) {
		if (dp[i] > best) {
			best = dp[i];
		}
	}

	return best;
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
	int arrLen = readIntArray(argv[2], arr);
	printf("%d\n", lis(n, arr, arrLen));
	return 0;
}

// gcc exp_twelve_lis.c -o output && ./output 8 10,22,9,33,21,50,41,60

// o/p:- 5