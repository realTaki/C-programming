#include<stdio.h>
#include<stdlib.h>
int a[100][2];

int as(void const *a, void const *b)
{
	return *((int*)a) + *((int*)a + 1) - (*((int*)b) + *((int*)b + 1));
}
main()
{
	int n;
	int i, j;
	scanf("%d", &n);
	for (i = 0; i < n; i++) scanf("%d%d", &a[i][0], &a[i][1]);
	qsort(a, n, sizeof(int) * 2, as);
	for (i = 0; i < n; i++) printf("%d %d\n", a[i][0], a[i][1]);

}