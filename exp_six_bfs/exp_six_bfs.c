#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * BreadthFirstSearch(int no_of_vertices, char *adjacencyMatrix) {
	// Write code here
	int adj[105][105] = {0};
	int row = 0, col = 0;

	// Step 1: Parse the space-separated adjacencyMatrix string into a 2D array
	for (int i = 0; adjacencyMatrix[i] != '\0'; i++) {
		if (adjacencyMatrix[i] == '0' || adjacencyMatrix[i] == '1') {
			adj[row][col] = adjacencyMatrix[i] - '0';
			col++;
			if (col == no_of_vertices) {
				col = 0;
				row++;
			}
		}
	}

	// Step 2: Perform BFS starting from vertex 0
	int visited[105] = {0};
	int queue[105];
	int front = 0, rear = 0;

	char *result = (char *)malloc(1000 * sizeof(char));
	result[0] = '\0';

	visited[0] = 1;
	queue[rear++] = 0;

	while (front < rear) {
		int curr = queue[front++];

		char temp[15];
		if (result[0] == '\0') {
			sprintf(temp, "%d", curr);
		} else {
			sprintf(temp, " %d", curr);
		}
		strcat(result, temp);

		for (int i = 0; i < no_of_vertices; i++) {
			if (adj[curr][i] == 1 && !visited[i]) {
				visited[i] = 1;
				queue[rear++] = i;
			}
		}
	}

	return result;
}

int main(int argc, char *argv[]) {
	int no_of_vertices = atoi(argv[1]);
	char *adjacencyMatrix = argv[2];
	printf("%s\n", BreadthFirstSearch(no_of_vertices, adjacencyMatrix));
	return 0;
}

// gcc exp_six_bfs.c -o output
// ./output 4 "0 1 1 1 1 0 1 1 1 1 0 1 1 1 1 0"
// o/p:- 0 1 2 3

// Adjacency Matrix:-
// 0   1   1   1
// 1   0   1   1
// 1   1   0   1
// 1   1   1   0
