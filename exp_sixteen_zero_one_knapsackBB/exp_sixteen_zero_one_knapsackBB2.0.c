
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxArrSize 100000

typedef struct {
    int w, p, id;
    double ratio;
} Item;

int best[1000], curr[1000];
long long maxProfit;
int nItems;

int cmp(const void *a, const void *b) {
    Item *x = (Item *)a, *y = (Item *)b;
    if (x->ratio < y->ratio) return 1;
    if (x->ratio > y->ratio) return -1;
    return 0;
}

double bound(int i, int weight, long long profit,
             Item a[], int n, int cap) {
    if (weight > cap) return 0;

    double b = profit;
    int j = i;
    int total = weight;

    while (j < n && total + a[j].w <= cap) {
        total += a[j].w;
        b += a[j].p;
        j++;
    }

    if (j < n)
        b += (cap - total) * a[j].ratio;

    return b;
}

void solve(int i, int weight, long long profit,
           Item a[], int n, int cap) {
    if (weight > cap) return;

    if (profit > maxProfit) {
        maxProfit = profit;
        for (int k = 0; k < n; k++)
            best[k] = curr[k];
    }

    if (i == n || bound(i, weight, profit, a, n, cap) <= maxProfit)
        return;

    // Include item i
    curr[i] = 1;
    solve(i + 1, weight + a[i].w, profit + a[i].p,
          a, n, cap);

    // Exclude item i
    curr[i] = 0;
    solve(i + 1, weight, profit, a, n, cap);
}

int fractional_knapsack(int n, int weights[], int weightsLen,
                        int values[], int valuesLen, int capacity,
                        short *resultsArr) {
    if (n <= 0 || n > 1000 || capacity < 0)
        return 0;

    Item a[1000];

    for (int i = 0; i < n; i++) {
        if (weights[i] <= 0) return 0;
        a[i].w = weights[i];
        a[i].p = values[i];
        a[i].id = i;
        a[i].ratio = (double)values[i] / weights[i];
    }

    qsort(a, n, sizeof(Item), cmp);

    maxProfit = 0;
    for (int i = 0; i < n; i++)
        best[i] = curr[i] = 0;

    solve(0, 0, 0, a, n, capacity);

    int count = 0;

    // Return chosen weights in original input order
    for (int original = 0; original < n; original++) {
        for (int j = 0; j < n; j++) {
            if (a[j].id == original && best[j]) {
                resultsArr[count++] = (short)a[j].w;
                break;
            }
        }
    }

    return count;
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

// o/p:- 20,30