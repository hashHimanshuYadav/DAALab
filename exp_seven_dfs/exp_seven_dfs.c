#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * depthFirstSearch(int no_of_vertices, char *adjacencyMatrix) {
	// Write code here
	int adj[100][100] = {0};
	int row = 0, col = 0;

	// Parse adjacency matrix string into a 2D array
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

	int visited[100] = {0};
	int stack[100];
	int top = -1;

	char *result = (char *)malloc(1000 * sizeof(char));
	result[0] = '\0';

	// Push starting vertex 0 onto the stack
	stack[++top] = 0;

	while (top >= 0) {
		int curr = stack[top--];

		if (!visited[curr]) {
			visited[curr] = 1;

			char temp[20];
			if (result[0] == '\0') {
				sprintf(temp, "%d", curr);
			} else {
				sprintf(temp, " %d", curr);
			}
			strcat(result, temp);
		}

		// Push unvisited neighbors in descending order 
		// so that the smallest index is processed first (LIFO order)
		for (int i = no_of_vertices - 1; i >= 0; i--) {
			if (adj[curr][i] == 1 && !visited[i]) {
				stack[++top] = i;
			}
		}
	}

	return result;
}

int main(int argc, char *argv[]) {
	int no_of_vertices = atoi(argv[1]);
	char *adjacencyMatrix = argv[2];
	printf("%s\n", depthFirstSearch(no_of_vertices, adjacencyMatrix));
	return 0;
}

// gcc exp_seven_dfs.c -o output
// ./output 4 "0 1 1 1 1 0 1 1 1 1 0 1 1 1 1 0"

// o/p:- 0 1 2 3

// Adjacency Matrix:-
// 0   1   1   1
// 1   0   1   1
// 1   1   0   1
// 1   1   1   0
