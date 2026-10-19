#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long matrix_chain_multiplication(int n, int dim[], int dimLen) {
	long long dp[101][101];   // dp[i][j] = min cost to multiply matrices i to j
	int i, j, k, len;
	long long cost;

	// one matrix alone needs 0 multiplications
	for (i = 1; i <= n; i++) {
		dp[i][i] = 0;
	}

	// len = how many matrices are in the chain (2, 3, ... n)
	for (len = 2; len <= n; len++) {
		for (i = 1; i <= n - len + 1; i++) {
			j = i + len - 1;
			dp[i][j] = 1000000000000000000LL;   // very big number

			// try every place k to split the chain into (i..k) and (k+1..j)
			for (k = i; k < j; k++) {
				cost = dp[i][k] + dp[k + 1][j]
				       + (long long)dim[i - 1] * dim[k] * dim[j];
				if (cost < dp[i][j]) {
					dp[i][j] = cost;
				}
			}
		}
	}

	return (long)dp[1][n];
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
	int dim[strlen(argv[2])];
	int dimLen = readIntArray(argv[2], dim);
	printf("%ld\n", matrix_chain_multiplication(n, dim, dimLen));
	return 0;
}

// gcc exp_thirteen_mcm.c -o output && ./output 3 5,10,20,15
// o/p:- 2500