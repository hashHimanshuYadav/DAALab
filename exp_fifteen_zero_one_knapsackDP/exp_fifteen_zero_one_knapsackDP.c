#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long knapsack(int n, int weights[], int weightsLen, int values[], int valuesLen, int capacity) {
	int i, w;
	long long result;

	// dp[w] = best value we can get with capacity w (all start at 0)
	long long *dp = (long long *)calloc(capacity + 1, sizeof(long long));

	if (dp == NULL) {
		return 0;
	}

	for (i = 0; i < n; i++) {
		// go from big capacity down to small, so each item is used only once
		for (w = capacity; w >= weights[i]; w--) {
			if (dp[w - weights[i]] + values[i] > dp[w]) {
				dp[w] = dp[w - weights[i]] + values[i];
			}
		}
	}

	result = dp[capacity];
	free(dp);
	return (long)result;
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
	int weights[strlen(argv[2])];
	int values[strlen(argv[3])];
	int capacity = atoi(argv[4]);
	int weightsLen = readIntArray(argv[2], weights);
	int valuesLen = readIntArray(argv[3], values);
	printf("%ld\n", knapsack(n, weights, weightsLen, values, valuesLen, capacity));
	return 0;
}

// gcc exp_fifteen_zero_one_knapsack.c -o output && ./output 3 10,20,30 60,100,120 50

// o/p:- 220