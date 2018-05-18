#include<stdio.h>
main() {
	char *a[3] = { "one","two","three" };
	char **p = a;
	printf("%s##", *(++p) + 1);
	printf("%c##", **p - 1);
}