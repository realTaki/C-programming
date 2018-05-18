#include<stdio.h>

main() {
	int n, i, j, k;
	int A[50][50] = { 0 };
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &A[i][j]);
		}
	}
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++)
				A[j][k] = A[j][k] || (A[j][i] && A[i][k]);
					
		}
	}
	for (i = 0; i < n;i++) {
		for (j = 0; j < n; j++){
			printf("%d", A[i][j]);
		}
		puts("\n");
	}
}