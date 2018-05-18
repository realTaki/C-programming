#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#define MAX_LEN 15 //字符串最大长度
#define STU_NUM 50 //最多的学生人数
#define COURSE_NUM 8 //最多的考试科目数

typedef struct student
{
	char num[MAX_LEN]; //每个学生的学号
	char name[MAX_LEN]; //每个学生的姓名
	float score[COURSE_NUM]; //每个学生COURSE_LEN门功课的成绩
	float sum; //每个学生的总成绩
	float aver; //每个学生的平均成绩
	float point; //每个学生的平均学分绩
}STU;

int Menu(void);
int Ascending(float a, float b);
int Descending(float a, float b);
void SwapFloat(float *x, float *y);
void SwapLong(long *x, long *y);
void SwapChar(char x[], char y[]);
void AsSortbyNum(STU stu[], int n, int m);
void GradePoint(STU stu[], int n, int m);
void ReadScore(STU stu[], int n, int m);
void AverSumofEveryStudent(STU stu[], int n, int m);
void AverSumofEveryCourse(STU stu[], int n, int m);
void SortbyScore(STU stu[], int n, int m, int(*compare)(float a, float b));
void PrintScore(STU stu[], int n, int m);
void WritetoFile(STU record[], int n, int m);
void ReadfromFile(STU record[], int *n, int *m);
void SortbyName(STU stu[], int n, int m);
void SearchbyNum(STU stu[], int n, int m);
void SearchbyName(STU stu[], int n, int m);
void StatisticAnalysis(STU stu[], int n, int m);


/*  函数功能：主函数，提示用户输入各项数据并按需求调用各项函数
函数入口参数：无
函数返回值：程序正常结束返回0
*/
int main()
{
	system("color 80");
	char input;
	int n = 0, m = 0; //学生人数为n,课程数m

	STU stu[STU_NUM];

	printf("\n*\t*\t*\t*\t欢迎进入学生成绩管理系统\t*\t*\t*\t*\n\n");
	printf("请输入学生人数（50人之内）\n>>>: ");

	while (scanf("%d", &n) != 1 || n > 50 || n <= 0)
	{
		while (getchar() != '\n');
		printf("请重新输入学生人数（50人之内）\n>>>: ");

	}
	printf("请输入课程数目（8门之内）\n>>>: ");

	while (scanf("%d", &m) != 1 || m > 8 || m <= 0)
	{
		while (getchar() != '\n');
		printf("请重新输入课程数目（8门之内）\n>>>:　");

	}
	printf("\n");

	while (1)
	{
		input = Menu();    //显示菜单，并读取用户输入
		switch (input)
		{
		case 0:  printf("\n                                                欢迎您下次使用！                                           \n");
			exit(1);
		case 1: ReadScore(stu, n, m);
			break;
		case 2: AverSumofEveryCourse(stu, n, m);
			break;
		case 3: AverSumofEveryStudent(stu, n, m);
			break;
		case 4: SortbyScore(stu, n, m, Descending);
			printf("\n按总分从高到低排序：\n");
			PrintScore(stu, n, m);
			break;
		case 5: SortbyScore(stu, n, m, Ascending);
			printf("\n按总分从低到高排序：\n");
			PrintScore(stu, n, m);
			break;
		case 6: AsSortbyNum(stu, n, m);
			printf("\n按学号从小到大排序：\n");
			PrintScore(stu, n, m);
			break;
		case 7: SortbyName(stu, n, m);
			printf("\n按姓名的字典顺序排序：\n");
			PrintScore(stu, n, m);
			break;
		case 8: SearchbyNum(stu, n, m);
			break;
		case 9: SearchbyName(stu, n, m);
			break;
		case 10: StatisticAnalysis(stu, n, m);
			break;
		case 11: PrintScore(stu, n, m);
			break;
		case 12: GradePoint(stu, n, m);
			break;
		case 13: WritetoFile(stu, n, m);
			break;
		case 14: ReadfromFile(stu, &n, &m);
			break;

		default: printf("输入错误！");
		}
	}
	return 0;
}



/*  函数功能：计算每个学生各门课程的总分和平均分
函数入口参数：结构体数组stu[],整形变量n表示学生人数，整形变量m表示课程门数
函数返回值：无
*/
void AverSumofEveryStudent(STU students[], int n, int m)
{
	int i, j;

	for (i = 0; i<n; i++)
	{
		students[i].sum = 0;
		for (j = 0; j<m; j++)
		{
			students[i].sum = students[i].sum + students[i].score[j];
		}
		students[i].aver = m>0 ? students[i].sum / m : -1;
		printf("学生 %d: 总成绩 ： %.0f, 平均分 ： %.0f\n", i + 1, students[i].sum, students[i].aver);
	}
}

/*  函数功能：显示菜单并获得用户键盘输入的选项
函数入口参数：
函数返回值：返回用户键盘输入的选项itemSelected
*/
int Menu(void)
{
	int itemSelected;
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
	printf("* 1.录入每个学生的学号、姓名和各科考试成绩\t\t\t\t*\n");
	printf("* 2.计算每门课程的总分和平均分\t\t\t\t\t\t*\n");
	printf("* 3.计算每个学生的总分和平均分\t\t\t\t\t\t*\n");
	printf("* 4.按每个学生的总分从高到低排出成绩表\t\t\t\t\t*\n");
	printf("* 5.按每个学生的总分从低到高排出成绩表\t\t\t\t\t*\n");
	printf("* 6.按学号由小到大排出成绩表\t\t\t\t\t\t*\n");
	printf("* 7.按姓名的字典顺序排出成绩表\t\t\t\t\t\t*\n");
	printf("* 8.按学号查询学生姓名及其考试成绩\t\t\t\t\t*\n");
	printf("* 9.按姓名查询学生学号及其考试成绩\t\t\t\t\t*\n");
	printf("* 10.成绩数据分析\t\t\t\t\t\t\t*\n");
	printf("* 11.输出每个学生的学号、姓名、各科考试成绩以及每门课程的总分和平均分\t*\n");
	printf("* 12.计算每位学生的平均学分绩\t\t\t\t\t\t*\n");
	printf("* 13.将每个学生的记录信息写入文件\t\t\t\t\t*\n");
	printf("* 14.从文件读取每个学生的记录信息\t\t\t\t\t*\n");
	printf("* 0. 退出系统\t\t\t\t\t\t\t\t*\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
	printf("\n请输入您的选择:\n>>>: ");
	scanf("%d", &itemSelected);    //读入用户输入
	return itemSelected;
}






/*  函数功能：按照选择法将数组sum的元素值排序
函数入口参数：结构体数组stu[],整形变量n表示学生人数，整形变量m表示课程门数,指向Ascending和Descending的函数指针*compare
函数返回值：无
*/
void SortbyScore(STU stu[], int n, int m, int(*compare)(float a, float b))
{
	int i, j, k, t;

	for (i = 0; i<n - 1; i++)
	{
		k = i;
		for (j = i + 1; j<n; j++)
		{
			if ((*compare)(stu[j].sum, stu[k].sum))
				k = j;
		}
		if (k != i)
		{
			for (t = 0; t<m; t++)    //交换m门课程的成绩
			{
				SwapFloat(&stu[k].score[t], &stu[i].score[t]);
			}
			SwapFloat(&stu[k].sum, &stu[i].sum);    //交换总分
			SwapFloat(&stu[k].aver, &stu[i].aver);    //交换平均分
			SwapChar(stu[k].num, stu[i].num);    //交换学号
			SwapChar(stu[k].name, stu[i].name);    //交换姓名
		}
	}
}

/*  函数功能：输入n个学生的m门课程成绩
函数入口参数：结构体数组stu[]，整形变量n表示学生人数，整形变量m表示课程门数
函数返回值：无
*/
void ReadScore(STU students[], int n, int m)
{
	int i, j;

	printf("请输入学生的学号、姓名和成绩\n");
	for (i = 0; i<n; i++)
	{
		scanf("%s%s", students[i].num, students[i].name);
		for (j = 0; j<m; j++)
		{
			scanf("%f", &students[i].score[j]);
		}
	}
	printf("\n");
}



/*  函数功能：交换两个浮点数内存位置
函数入口参数：需要交换的两个浮点数
函数返回值：无
*/
void SwapFloat(float *x, float *y)
{
	float tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

/*  函数功能：交换两个长整形数内存位置
函数入口参数：需要交换的两个长整型数
函数返回值：无
*/
void SwapLong(long *x, long *y)
{
	long tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}


/*  函数功能：计算每门课程的总分和平均分
函数入口参数：结构体数组stu[],整形变量n表示学生人数，整形变量m表示课程门数
函数返回值：无
*/
void AverSumofEveryCourse(STU stu[], int n, int m)
{
	int i, j;
	float sum[COURSE_NUM], aver[COURSE_NUM];

	for (j = 0; j<m; j++)
	{
		sum[j] = 0;
		for (i = 0; i<n; i++)
		{
			sum[j] = sum[j] + stu[i].score[j];
		}
		aver[j] = n>0 ? sum[j] / n : -1;
		printf("课程 %d: 总分 ： %.0f, 平均分 ： %.0f\n", j + 1, sum[j], aver[j]);
	}
}

/*  函数功能：使数据升序排序
函数入口参数：需要比较的两个浮点数
函数返回值：返回比较结果的布尔值
*/
int Ascending(float a, float b)
{
	return a < b;    //这样比较决定了按升序排序，如果a<b，则交换
}

/*  函数功能：使数据降序排序
函数入口参数：需要比较的两个浮点数
函数返回值：返回比较结果的布尔值
*/
int Descending(float a, float b)
{
	return a > b;    //这样比较决定了按降序排序，如果a>b，则交换
}




/*  函数功能：按学号查找学生成绩并显示查找结果
函数入口参数：结构体数组stu[],整形变量n表示学生人数，整形变量m表示课程门数
函数返回值：无
*/
void SearchbyNum(STU stu[], int n, int m)
{
	char numbers[MAX_LEN];
	int i, j;

	printf("请输入想要查找的学号：");
	scanf("%s", numbers);    //输入想要查找的学号
	for (i = 0; i<n; i++)
	{
		if (strcmp(stu[i].num, numbers) == 0)    //查到
		{
			printf("%s\t%s\t", stu[i].num, stu[i].name);    //输出该学号以及对应姓名
			for (j = 0; j<m; j++)
			{
				printf("%.0f\t", stu[i].score[j]);    //输出该学号对应的m门课程的成绩
			}
			printf("%.0f\t%.0f\n", stu[i].sum, stu[i].aver);    //输出该学号对应的总分和平均分
			return;
		}
	}
	printf("没有发现该学生！\n");
}


/*  函数功能：按选择法将字符数组num的元素按顺序排列
函数入口参数：结构体数组stu[],整形变量n表示学生人数，整形变量m表示课程门数
函数返回值：无
*/
void AsSortbyNum(STU stu[], int n, int m)
{
	int i, j, k;

	for (i = 0; i<n - 1; i++)
	{
		for (j = i + 1; j<n; j++)
		{
			if (strcmp(stu[j].num, stu[i].num) < 0)
			{
				for (k = 0; k<m; k++)    //交换m门课程的成绩
				{
					SwapFloat(&stu[i].score[k], &stu[j].score[k]);
				}
				SwapFloat(&stu[i].sum, &stu[j].sum);    //交换总分
				SwapFloat(&stu[i].aver, &stu[j].aver);    //交换平均分
				SwapChar(stu[i].num, stu[j].num);    //交换学号
				SwapChar(stu[i].name, stu[j].name);    //交换姓名
			}
		}
	}
}

/*  函数功能：交换法实现字符串按字典顺序排序
函数入口参数：结构体数组stu[],整形变量n表示学生人数，整形变量m表示课程门数
函数返回值：无
*/
void SortbyName(STU stu[], int n, int m)
{
	int i, j, k;

	for (i = 0; i<n - 1; i++)
	{
		for (j = i + 1; j<n; j++)
		{
			if (strcmp(stu[j].name, stu[i].name) < 0)
			{
				for (k = 0; k<m; k++)    //交换m门课程的成绩
				{
					SwapFloat(&stu[i].score[k], &stu[j].score[k]);
				}
				SwapFloat(&stu[i].sum, &stu[j].sum);    //交换总分
				SwapFloat(&stu[i].aver, &stu[j].aver);    //交换平均分
				SwapChar(stu[i].num, stu[j].num);    //交换学号
				SwapChar(stu[i].name, stu[j].name);    //交换姓名
			}
		}
	}
}

/*  函数功能：按姓名查找学生成绩并显示查找结果
函数入口参数：结构体数组stu[],整形变量n表示学生人数，整形变量m表示课程门数
函数返回值：无
*/
void SearchbyName(STU stu[], int n, int m)
{
	char x[MAX_LEN];
	int i, j;

	printf("请输入想要查找的姓名：");
	scanf("%s", x);    //输入想要查找的姓名
	for (i = 0; i<n; i++)
	{
		if (strcmp(stu[i].name, x) == 0)    //查到
		{
			printf("%s\t%s\t", stu[i].num, stu[i].name);    //输出该姓名以及对应学号
			for (j = 0; j<m; j++)
			{
				printf("%.0f\t", stu[i].score[j]);    //输出该姓名对应的m门课程的成绩
			}
			printf("%.0f\t%.0f\n", stu[i].sum, stu[i].aver);    //输出该姓名对应的总分和平均分
			return;
		}
	}
	printf("没有发现该学生！\n");
}


/*  函数功能：从文件中读取学生的学号、姓名及成绩等信息写入到结构体数组stu中
函数入口参数：学生数据数组stu[]，学生人数n，课程数m
函数返回值：无
*/
void ReadfromFile(STU stu[], int *n, int *m)
{
	FILE *fp;
	int i, j;
	if ((fp = fopen("student.txt", "r")) == NULL)
	{
		printf("打开文件失败！\n");
		exit(0);
	}
	fscanf(fp, "%d\t%d", n, m);  //从文件中读出学生人数和课程门数
	for (i = 0; i<*n; i++)  //学生人数保存在n指向的存储单元
	{
		fscanf(fp, "%10s", stu[i].num);
		fscanf(fp, "%10s", stu[i].name);
		for (j = 0; j<*m; j++)  //课程门数保存在n指向的存储单元
		{
			fscanf(fp, "%10f", &stu[i].score[j]);
		}
		fscanf(fp, "%10f%10f", &stu[i].sum, &stu[i].aver);
	}
	fclose(fp);
}


/*  函数功能：交换两个字符串的内存位置
函数入口参数：需要交换的两个字符串
函数返回值：无
*/
void SwapChar(char x[], char y[])
{
	char tmp[MAX_LEN];
	strcpy(tmp, x);
	strcpy(x, y);
	strcpy(y, tmp);
}



/*  函数功能：打印学生成绩
函数入口参数：学生数据数组stu[]，学生人数n，课程数m
函数返回值：无
*/
void PrintScore(STU stu[], int n, int m)
{
	int i, j;

	for (i = 0; i<n; i++)
	{
		printf("%s\t%s\t", stu[i].num, stu[i].name);    //打印学号和姓名
		for (j = 0; j<m; j++)
		{
			printf("%.0f\t", stu[i].score[j]);    //打印m门课程的成绩
		}
		printf("%.0f\t%.0f\n", stu[i].sum, stu[i].aver);    //打印总分和平均分
	}
}




/*  函数功能：输出n个学生的学号、姓名及m门课程的成绩到文件student.txt中
函数入口参数：学生数据数组stu[]，学生人数n，课程数m
函数返回值：无
*/
void WritetoFile(STU stu[], int n, int m)
{
	FILE *fp;
	int i, j;
	if ((fp = fopen("student.txt", "w")) == NULL)
	{
		printf("打开文件失败！\n");
		exit(0);
	}
	fprintf(fp, "%d\t%d\n", n, m);  //将学生人数和课程门数写入文件
	for (i = 0; i<n; i++)
	{
		fprintf(fp, "%10s%10s", stu[i].num, stu[i].name);
		for (j = 0; j<m; j++)
		{
			fprintf(fp, "%10.0f", stu[i].score[j]);
		}
		fprintf(fp, "%10.0f%10.0f\n", stu[i].sum, stu[i].aver);
	}
	fclose(fp);
}


/*  函数功能：计算平均学分绩
函数入口参数：学生数据数组stu[]，学生人数n，课程数m
函数返回值：无
*/
void GradePoint(STU stu[], int n, int m)
{
	float grade[COURSE_NUM];
	int i, j, sum = 0;

	printf("请输入每门课程的学分：");
	for (i = 0; i<m; i++)
	{
		scanf("%f", &grade[i]);
		sum += grade[i];
	}
	for (i = 0; i<n; i++)
	{
		stu[i].point = 0;
		for (j = 0; j<m; j++)
		{
			stu[i].point += (stu[i].score[j])*grade[j];
		}
		printf("学生 %d: 平均学分绩: %.0f\n", i + 1, (stu[i].point) / sum);
	}
}



/*  函数功能：统计各分数段的学生人数及所占的百分比
函数入口参数：结构体数组stu[],整形变量n表示学生人数，整形变量m表示课程门数
函数返回值：无
*/
void StatisticAnalysis(STU stu[], int n, int m)
{
	int i, j, t[6];

	for (j = 0; j<m; j++)
	{
		printf("对于课程%d:\n", j + 1);
		memset(t, 0, sizeof(t));    //将数组t的全部元素初始化为零
		for (i = 0; i<n; i++)
		{
			if (stu[i].score[j] >= 0 && stu[i].score[j]<60) t[0]++;
			else if (stu[i].score[j]<70)   t[1]++;
			else if (stu[i].score[j]<80)   t[2]++;
			else if (stu[i].score[j]<90)   t[3]++;
			else if (stu[i].score[j]<100)  t[4]++;
			else if (stu[i].score[j] == 100) t[5]++;
		}
		for (i = 0; i <= 5; i++)
		{
			if (i == 0)
				printf("<60\t%d\t%.2f%%\n", t[i], (float)t[i] / n * 100);    //不及格人数及百分比
			else if (i == 5)
				printf("%d\t%d\t%.2f%%\n", (i + 5) * 10, t[i], (float)t[i] / n * 100);    //满分人数及百分比
			else printf("%d-%d\t%d\t%.2f%%\n", (i + 5) * 10, (i + 5) * 10 + 9, t[i], (float)t[i] / n * 100); //其他分数段人数及百分比
		}
	}
}



