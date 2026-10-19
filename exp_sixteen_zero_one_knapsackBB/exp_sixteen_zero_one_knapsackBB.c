#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxArrSize 100000

int fractional_knapsack(int n, int weights[], int weightsLen, int values[], int valuesLen, int capacity, short *resultsArr) {
    int dp[105][1005];

    // Builds standard DP table for 0/1 Knapsack
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                int take = values[i - 1] + dp[i - 1][w - weights[i - 1]];
                int skip = dp[i - 1][w];
                dp[i][w] = (take > skip) ? take : skip;
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Set the maximum total profit to the output array
    resultsArr[0] = (short)dp[n][capacity];
    
    // Return length 1 so printArrayElements prints 220
    return 1;
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

void printArrayElements(short *resultsArr, int resultsArrLength) {
    int index;
    for (index = 0; index < resultsArrLength - 1; index++) {
        printf("%d,", resultsArr[index]);
    }
    printf("%d\n", resultsArr[index]);
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int weights[strlen(argv[2])];
    int values[strlen(argv[3])];
    int capacity = atoi(argv[4]);
    int weightsLen = readIntArray(argv[2], weights);
    int valuesLen = readIntArray(argv[3], values);
    short resultsArr[MaxArrSize];
    int resultsArrLength = fractional_knapsack(n, weights, weightsLen, values, valuesLen, capacity, resultsArr);
    printArrayElements(resultsArr, resultsArrLength);
    return 0;
}

// gcc exp_sixteen_zero_one_knapsackBB.c -o output && ./output 3 10,20,30 60,100,120 50

// o/p:- 220