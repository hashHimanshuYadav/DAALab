#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long primsAlgorithm(int no_of_vertices, char *adjacencyMatrix) {
	int n = no_of_vertices;
	int graph[100][100];
	int key[100];
	int visited[100];
	int i, j, count, u, min;
	long total = 0;
	char *token;

	// read the numbers from the string into graph[][]
	token = strtok(adjacencyMatrix, " ");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			graph[i][j] = atoi(token);
			token = strtok(NULL, " ");
		}
	}

	// all keys big, nothing visited
	for (i = 0; i < n; i++) {
		key[i] = 1000000;
		visited[i] = 0;
	}
	key[0] = 0;   // start from vertex 0

	for (count = 0; count < n; count++) {

		// find the unvisited vertex with the smallest key
		min = 2000000;
		u = -1;
		for (i = 0; i < n; i++) {
			if (visited[i] == 0 && key[i] < min) {
				min = key[i];
				u = i;
			}
		}

		if (u == -1) {
			break;
		}

		visited[u] = 1;
		total = total + key[u];

		// update the keys of its neighbours
		for (j = 0; j < n; j++) {
			if (graph[u][j] != 0 && visited[j] == 0 && graph[u][j] < key[j]) {
				key[j] = graph[u][j];
			}
		}
	}

	return total;
}

int main(int argc, char *argv[]) {
	int no_of_vertices = atoi(argv[1]);
	char *adjacencyMatrix = argv[2];
	printf("%ld\n", primsAlgorithm(no_of_vertices, adjacencyMatrix));
	return 0;
}

// gcc exp_nine_prims.c -o output
// ./output 4 "0 1 2 4 1 0 0 3 2 0 0 5 4 3 5 0"

// o/p:- 6