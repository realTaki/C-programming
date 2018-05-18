#include<stdio.h>
#include<math.h>
int count = 0;//此问题效率与判断素数的时候if使用次数成反比
int Isprime(int n) {//判断素数
	int i;
	for (i = 3; i <= sqrt(n); i++)
	{ count++; if (!(n%i))return 0; }
	return 1;
}
void counter(int m, int mode) {//核心算法
	int i,flag=0;
	if (!((m / 2) % 2))flag=1;//判断二分点是否奇数，若不是，加减1使之为奇数
	if (mode == 1)
	{for (i = m / 2+flag; i < m; i+=2)if (Isprime(i)&&Isprime(m - i))printf("(%d,%d)", i, m - i);}
	else {for (i = m / 2-flag; i>0 ; i-=2)if (Isprime(i)&&Isprime(m - i))printf("(%d,%d)", i, m - i);}
	printf("\nif的使用次数:%d\n", count);
}
int main() {//控制主体
	int numble = 1,mode=-1;
	char c=0;
	 do{
		numble = 1, mode = -1; count = 0; c = 0;
		while (numble % 2)
		{
			printf("请输入一个偶数:"); scanf("%d", &numble);
		}
		while (mode != 1 && mode != 0)
		{
			printf("输入1向上检索,输入0向下检索:"); scanf("%d", &mode);
		}
		counter(numble, mode);
		printf("按任意键继续,按ESC退出\n");
	 } while ( getch()!= 27);
	return 0;
}