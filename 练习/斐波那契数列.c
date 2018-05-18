#include<stdio.h>
int Fact(int a, int *p);
int main()
{
	int *p;
	int n, i, a,count=0;
	p = &count;
	printf("Input n:");
	scanf("%d", &n);
	for (i = 0; i <= n; i++)
	{

		a = Fact(i, p);
		printf("Fib(%d)=%d, count=%d\n", i, a, *p);
	}

	return 0;
}

int Fact(int a, int*p)
{
	if (a == 0)
	{
		*p++;
		return 0;
	}
	else if (a == 1)
	{
		*p++;
		return 1;
	}
	else
	{
		*p++;
		return Fact(a - 1, p) + Fact(a - 2, p);
	}
}