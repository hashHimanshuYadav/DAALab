#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dp[1001][1001];   // global, so it doesn't use up stack memory

int LCS(char *str1, char *str2) {
	int n = strlen(str1);
	int m = strlen(str2);
	int i, j;

	// row 0 and column 0 are 0 (empty string has no common part)
	for (i = 0; i <= n; i++) {
		for (j = 0; j <= m; j++) {
			if (i == 0 || j == 0) {
				dp[i][j] = 0;
			}
			else if (str1[i - 1] == str2[j - 1]) {
				// characters match: 1 + the answer without both characters
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				// no match: take the better of skipping one character
				if (dp[i - 1][j] > dp[i][j - 1]) {
					dp[i][j] = dp[i - 1][j];
				} else {
					dp[i][j] = dp[i][j - 1];
				}
			}
		}
	}

	return dp[n][m];
}

int main(int argc, char *argv[]) {
	char *str1 = argv[1];
	char *str2 = argv[2];
	printf("%d\n", LCS(str1, str2));
	return 0;
}
// gcc exp_eleven_lcs.c -o output
// ./output ABCBDAB BDCABA

// o/p:- 4