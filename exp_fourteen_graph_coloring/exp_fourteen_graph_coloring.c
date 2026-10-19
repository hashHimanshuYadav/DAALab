#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxArrSize 100000

int graph_coloring(int n, char *adjacencyMatrix, int m, int *resultsArr) {
	int g[100][100];
	int i, j, c, v, found, ok;
	char *token;

	// read the numbers from the string into g[][]
	token = strtok(adjacencyMatrix, " ");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			g[i][j] = atoi(token);
			token = strtok(NULL, " ");
		}
	}

	// 0 means "not colored yet"
	for (i = 0; i < n; i++) {
		resultsArr[i] = 0;
	}

	v = 0;   // current vertex
	while (v >= 0 && v < n) {
		found = 0;

		// try the next colors for vertex v (continue after its current color)
		for (c = resultsArr[v] + 1; c <= m; c++) {
			ok = 1;
			for (j = 0; j < n; j++) {
				if (g[v][j] == 1 && resultsArr[j] == c) {
					ok = 0;   // a neighbour already has this color
					break;
				}
			}
			if (ok == 1) {
				resultsArr[v] = c;
				found = 1;
				break;
			}
		}

		if (found == 1) {
			v++;               // move forward to the next vertex
		} else {
			resultsArr[v] = 0; // no color works: undo this vertex
			v--;               // go back to the previous vertex
		}
	}

	if (v < 0) {
		resultsArr[0] = -1;    // went back past vertex 0: impossible
		return -1;
	}
	return n;
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
	char *adjacencyMatrix = argv[2];
	int m = atoi(argv[3]);
	int resultsArr[MaxArrSize];
	int resultsArrLength = graph_coloring(n, adjacencyMatrix, m, resultsArr);
	printArrayElements(resultsArr, resultsArrLength);
	return 0;
}

// gcc exp_fourteen_graph_coloring.c -o output && ./output 4 "0 1 1 1 1 0 1 0 1 1 0 1 1 0 1 0" 3

// o/p:- 1,2,3,2