#include<stdio.h>
int isprime(int n) {
	int i;
	for (i = 2; i<sqrt(n); i++) {
		if (n%i == 0)return 1;
	}return 0;
}
void Print(int m) {
	int i;
	for (i = 2; i<m; i++)if (m%i == 0)printf("%d\n", i);
}
main() {
	int a;
	printf("Please enter a number:");
	scanf("%d", &a);
	if (a == 1 || a == -1 || a)printf("It is not a prime number.No divisor!\n");
	else if (isprime(a))Print(a);
	else printf("It is a prime number.No divisor!\n");
}