#include<stdio.h>
#include<string.h>
#define C *(str + i)

int main() {

	char str[2000];
	int n=0,i;
	scanf("%s", str);
	n=strlen(str);

	for (i = 0; i < n; i++) {
		if (C > 64 && C < 91) {
			C += 13;
			if (C > 90)C -= 26;
		}
		else if (C > 96 && C < 123) {
			C += 13;
			if (C > 122)C -= 26;
		}

	}
	printf("%s", str);

	return 0;
}