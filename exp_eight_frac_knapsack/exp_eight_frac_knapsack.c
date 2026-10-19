#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float fractional_knapsack(int n, int weights[], int weightslen, int values[], int valueslen, int capacity) {
	double ratio[n];

	// 1. Calculate value/weight for each item
	for (int i = 0; i < n; i++) {
		ratio[i] = (double)values[i] / weights[i];
	}

	// 2. Sort by ratio (highest first) using simple bubble sort,
	//    swapping weights and values along with the ratio
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (ratio[j] < ratio[j + 1]) {
				double tr = ratio[j];
				ratio[j] = ratio[j + 1];
				ratio[j + 1] = tr;

				int tw = weights[j];
				weights[j] = weights[j + 1];
				weights[j + 1] = tw;

				int tv = values[j];
				values[j] = values[j + 1];
				values[j + 1] = tv;
			}
		}
	}

	// 3. Fill the knapsack greedily
	double total = 0.0;
	int remaining = capacity;

	for (int i = 0; i < n && remaining > 0; i++) {
		if (weights[i] <= remaining) {
			// take the whole item
			total += values[i];
			remaining -= weights[i];
		} else {
			// take only a fraction of the item
			total += ratio[i] * remaining;
			remaining = 0;
		}
	}

	return (float)total;
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
	int weightslen = readIntArray(argv[2], weights);
	int valueslen = readIntArray(argv[3], values);
	int capacity = atoi(argv[4]);
	printf("%.1f\n", fractional_knapsack(n, weights, weightslen, values, valueslen, capacity));
	return 0;
}

// gcc exp_eight_frac_knapsack.c -o output
// ./output 3 10,20,30 60,100,120 50

// o/p:- 240.0