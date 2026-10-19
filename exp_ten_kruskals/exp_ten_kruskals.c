#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parent[100];

// find which group a vertex belongs to
int find(int x) {
	while (parent[x] != x) {
		x = parent[x];
	}
	return x;
}

long kruskalAlgorithm(int no_of_vertices, char *adjacencyMatrix) {
	int n = no_of_vertices;
	int graph[100][100];
	int eu[5000], ev[5000], ew[5000];   // edge: from, to, weight
	int e = 0;                          // number of edges
	int i, j, t;
	long total = 0;
	char *token;

	// Step 1: read the numbers from the string into graph[][]
	token = strtok(adjacencyMatrix, " ");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			graph[i][j] = atoi(token);
			token = strtok(NULL, " ");
		}
	}

	// Step 2: make a list of edges (only i < j so each edge is stored once)
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			if (graph[i][j] != 0) {
				eu[e] = i;
				ev[e] = j;
				ew[e] = graph[i][j];
				e++;
			}
		}
	}

	// Step 3: sort the edges by weight, smallest first
	for (i = 0; i < e - 1; i++) {
		for (j = 0; j < e - i - 1; j++) {
			if (ew[j] > ew[j + 1]) {
				t = ew[j]; ew[j] = ew[j + 1]; ew[j + 1] = t;
				t = eu[j]; eu[j] = eu[j + 1]; eu[j + 1] = t;
				t = ev[j]; ev[j] = ev[j + 1]; ev[j + 1] = t;
			}
		}
	}

	// Step 4: at the start, every vertex is in its own group
	for (i = 0; i < n; i++) {
		parent[i] = i;
	}

	// Step 5: go through edges from smallest to largest
	for (i = 0; i < e; i++) {
		int a = find(eu[i]);
		int b = find(ev[i]);

		// different groups means no cycle, so take this edge
		if (a != b) {
			total = total + ew[i];
			parent[a] = b;   // join the two groups
		}
	}

	return total;
}

int main(int argc, char *argv[]) {
	int no_of_vertices = atoi(argv[1]);
	char *adjacencyMatrix = argv[2];
	printf("%ld\n", kruskalAlgorithm(no_of_vertices, adjacencyMatrix));
	return 0;
}

// gcc kruskal.c -o output
// ./output 5 "0 40 0 0 70 40 0 30 40 0 0 30 0 90 50 0 40 90 0 20 70 0 50 20 0"

// o/p:- 130