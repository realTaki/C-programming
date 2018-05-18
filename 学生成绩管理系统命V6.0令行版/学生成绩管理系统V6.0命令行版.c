#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

#define STUDENTS 30	//学生人数
#define COURSE 6	//课程数上限
#define NAME 15		//姓名长度上限
#define MAXLEN 7	//单条命令长度上限

typedef struct MyStruct
{
	long number;		//学号
	int totalscore;		//总分
	double averscore;	//平均分
	int score[COURSE];	//各科成绩
	char name[NAME];	//姓名
}STU;   //用于存储学生信息的结构体

typedef struct MyStruct2
{
	int courseN;			//课程数
	int Iniflag;			//初始化状态
	int Successfulnumber;	//已登记人数
	int sortflag;			//当前排序状态	
}FLAG;	//用于存储程序运行状态的结构体

int Initialization(FLAG *flag);

int AnalyzeOrder(char ml[], int x);
/*功能:分析用户输入的命令
参数:存储用户输入的命令的数组,以及命令类型
返回值:对应命令的数字记号
*/
int SearchStudent(FLAG*flag, STU student[], int x);
/*功能:按条件查询学生信息
参数:flag是本程序各项状态的集合,student[]是所有学生信息,x为查询的类型
返回值:对应学生在所有学生信息数组中的下标
*/
void NewStudent(FLAG *flag, STU student[]);
/*功能:批量新建学生信息
参数:flag是本程序各项状态的集合,student[]用于存储所有学生信息
返回值:无
*/
void ModifyStudent(FLAG *flag, STU student[]);
/*功能:修改指定学生信息
参数:flag是本程序各项状态的集合,student[]用于存储所有学生信息
返回值:无
*/
void ReadStudent(FLAG *flag, STU stu[]);
/*功能:读取文件中的学生信息
参数:flag是本程序各项状态的集合,student[]用于存储所有学生信息
返回值:无
*/
void ListStudent(FLAG*flag, STU student[]);
/*功能:按要求分析用户的排序指令,并最终按要求打印学生成绩单
参数:flag是本程序各项状态的集合,student[]用于存储所有学生信息
返回值:无
*/
void DeleteStudent(FLAG *flag, STU student[]);
/*功能:引导用户删除指定学生信息
参数:flag是本程序各项状态的集合,student[]用于存储所有学生信息
返回值:无
*/
void WriteStudent(FLAG *flag, STU student[],int x);
/*功能:将学生信息输出到对应文件中
参数:flag是本程序各项状态的集合,student[]用于存储所有学生信息
返回值:无
*/
void SortName(FLAG *flag, STU student[], int mode);
/*功能:对学生信息按照姓名进行排序
参数:flag是本程序各项状态的集合,student[]用于存储所有学生信息
返回值:无
*/
void SortScore(FLAG *flag, STU student[], int mode);
/*功能:对学生信息按照总分进行排序
参数:flag是本程序各项状态的集合,student[]用于存储所有学生信息
返回值:无
*/
void SortNumber(FLAG *flag, STU student[], int mode);
/*功能:对学生信息按照学号进行排序
参数:flag是本程序各项状态的集合,student[]用于存储所有学生信息
返回值:无
*/
void PrintStudent(FLAG*flag, STU student[], int x);
/*功能:输出学生的成绩单
参数:flag是本程序各项状态的集合,student[]用于存储所有学生信息,x是指定输出的学生下标
返回值:无
*/
void Swap(STU *x,STU *y);
/*功能:交换学生信息存储的位置
参数:需要交换位置的两项学生信息
返回值:无
*/
void ViewHelp(void);
/*功能:各项帮助信息导航
参数:无
返回值:无
*/
void PutMenu(void);
/*功能:打印功能菜单
参数:无
返回值:无
*/

int main(int argc, char* arvg[])
{	
	STU student[STUDENTS];		//储存所有学生信息的数组
	FLAG Flag = { -1,1,0 ,0 };	//定义用于存储程序各项运行状态的结构体
	int  i;
	char ml[MAXLEN] = { 0 };

	//欢迎界面
	puts("欢迎使用学生成绩管理终端! --作者HIT1163710227黑川");
	PutMenu();
	ReadStudent(&Flag, student);

	//开始程序
	while (Initialization(&Flag)) {
		printf("\n请输入命令进行操作:>>> ");
		while (!scanf("%4s", ml))//错误检查
		{
			puts("无效命令，请重新输入\n");
			while (getchar() != '\n');
		}
		switch (AnalyzeOrder(ml, 1))//分析指令并引导到各个功能函数
		{
		case 0:
			NewStudent(&Flag, student); break;
		case 1:
			DeleteStudent(&Flag, student);   break;
		case 2:
			ModifyStudent(&Flag, student);  break;
		case 3:
			i = -1;
			i = SearchStudent(&Flag, student, -1);
			if (i > -1)PrintStudent(&Flag, student, i); break;
		case 4:
			ListStudent(&Flag, student);  break;
		case 5:
			ReadStudent(&Flag, student);  break;
		case 6:
			WriteStudent(&Flag, student,0);  break;
		case 7:
			ViewHelp(); break;
		case 8:
			PutMenu(); break;
		case 9:
			WriteStudent(&Flag, student,1); exit(1); break;
		default:
			printf("'%s'不是有效命令,请重新输入:", ml); break;
		}
	}

	//特殊原因退出
	puts("异常退出!!!");
	return 0;
}

void PutMenu(void) {

	system("cls");//清屏

	printf("\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\
\t\t* 命令简介如下:								*\n\
\t\t* new n(n<=30) 新建学生信息						*\n\
\t\t* del name/number 按姓名/学号查找并删除学生信息				*\n\
\t\t* re  name/number 按姓名/学号查找并修改学生信息				*\n\
\t\t* sch name/number 按姓名/学号查找学生信息				*\n\
\t\t* ls  score/name/number asc/desc 按分数/学号/姓名 升序/降序 打印成绩单	*\n\
\t\t* rd  xxx 读取文件xxx							*\n\
\t\t* wr  xxx 导出文件于xxx							*\n\
\t\t* help xx 查看xx命令的详细帮助信息					*\n\
\t\t* menu 查看本菜单							*\n\
\t\t* exit 自动保存数据并退出程序						*\n\
\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
}

int Initialization(FLAG *flag) {
	if (flag->Iniflag) {//自动读档失败,要求用户手动输入各项参数
		printf("\n请输入本次考试有效科目数n,(n<=6):\n");
		while (!scanf("%2d", &flag->courseN) ||flag->courseN >6 || flag->courseN<0)
		{
			puts("错误数据,请重新输入\n");
			while (getchar() != '\n');
		}
		flag->Iniflag = 0;
	}

	while(getchar() != '\n');//清空缓冲区
	return 1;
}

void NewStudent(FLAG *flag,STU student[]) {
	int n = flag->courseN,m=flag->Successfulnumber;
	int i=0, j=0, number = 0;

	//输入及输入检查
	if (!scanf("%2d", &number)||number<1||number+m >STUDENTS) {
		puts("输入的学生人数无效或越界,新建学生信息失败!");
	}else {//输入无误,读取学生信息,并计算总分平均分
		printf("请按如下格式输入%d个学生的信息:\n",number);
		printf("姓名\t学号");
		for (i = 0; i < n; i++)printf("\t科目%d", i + 1);
		printf("\n");
		for (i = 0; i < number; i++) {
			scanf("%14s%ld",student[m+i].name,&student[m+i].number);
			student[i].totalscore = 0;
			for (j = 0; j < n; j++) { 
				scanf("%3d", &student[m + i].score[j]);
				student[i].totalscore += student[i].score[j];
			}
			student[i].averscore = student[i].totalscore / flag->courseN;
			flag->Successfulnumber++;//每读取一名学生信息,成功读取信息人数加一
		}
	}
	flag->sortflag = -1;//有新信息写入,需要重新排序
}

void ModifyStudent(FLAG *flag, STU student[]) {
	char ml[7] = { 0 };
	int n = -1, x = -1, i =0;

	if (!scanf("%6s", ml))//读取命令并检查
	{
		puts("无效命令,请重新输入\n");
		return;
	}

	//分析命令并检索学生信息
	n = AnalyzeOrder(ml, 2);
	if (n == 1 || n == 2)x = SearchStudent(flag, student, n);
	else printf("'re %s'不是有效指令,请重新输入", ml);

	if (x != -1) {//引导用户修改学生信息
		printf("请按如下格式输入正确的学生信息:\n");
		printf("姓名\t学号");
		for (i = 0; i < n; i++)printf("\t科目%d", i + 1);
		printf("\n");
		scanf("%14s%ld", student[x].name, &student[x].number);
		student[x].totalscore = 0;
		for (i = 0; i < flag->courseN; i++) {
				scanf("%3d", &student[x].score[i]);
				student[x].totalscore += student[x].score[i];
			}
		student[x].averscore = student[x].totalscore / flag->courseN;
		flag->sortflag = -1;//有信息改动,需要重新排序
	}
}

void ReadStudent(FLAG *flag,STU student[]) {
	FILE *fp;
	char filename[20] = {0};
	char *file = "student.txt";
	int i, j;
	
	//打开文件
	if (flag->Iniflag ) {
		fp = fopen(file, "r");
	}else {
		while (!scanf("%19s", filename)) {
			puts("请输入正确文件地址及文件名");
			while (getchar() != '\n');
		}
		fp = fopen(filename, "r");
	}

	if (fp != NULL) {//打开成功则读取文件
		fscanf(fp,"%1d%2d",&flag->courseN,&flag->Successfulnumber);
		for (i = 0; i < flag->Successfulnumber; i++) {
			student[i].totalscore = 0;
			fscanf(fp, "%14s%ld", &student[i].name, &student[i].number);
			for (j = 0; j < flag->courseN; j++){
				fscanf(fp,"%3d",&student[i].score[j]);
				student[i].totalscore += student[i].score[j];
			}
			fscanf(fp, "%*d%*lf");
			student[i].averscore = student[i].totalscore / flag->courseN;
		}
		fclose(fp);
		flag->sortflag = -1;
		flag->Iniflag = 0;
		puts("读取存档成功,按回车键继续") ;
	}else if (flag->Iniflag)puts("自动读档失败!");
	else puts("读取失败!!!");//打开失败则根据原因报出错误
}

void WriteStudent(FLAG *flag, STU student[],int x) {
	FILE *fp;
	char filename[20] = { 0 };
	char *file = "student.txt";
	int i=0, j=0;

	//打开文件
	if (x) {
		fp = fopen(file, "w");
	}else {
		while (!scanf("%19s", filename)) {
			puts("请输入正确文件地址及文件名");
			while (getchar() != '\n');
		}
		fp = fopen(filename, "w");
	}

	if (fp != NULL) {//打开成功则输出学生信息
		fprintf(fp,"%d\t%d",flag->courseN,flag->Successfulnumber);
		for (i = 0; i < flag->Successfulnumber; i++) {
			fprintf(fp, "\n%s\t%ld", student[i].name,student[i].number);
			for (j = 0; j < flag->courseN; j++) {
				fprintf(fp, "\t%d", student[i].score[j]);
			}
			fprintf(fp, "\t%d\t%.1f",student[i].totalscore,student[i].averscore);
		}
		fclose(fp);
	}else puts("保存失败!");//打开失败则报错
}

void Swap(STU *x, STU *y) {//交换两项学生信息
	STU temp=*x;
	*x = *y;
	*y = temp;
}

void SortName(FLAG *flag,STU student[],int mode) {
	int i = 0, j = 0, k = 0;
	int temp;

	//如果已排序则无需重复排序
	if (flag->sortflag == 10+mode)return;
	for (i = 0; i < flag->Successfulnumber - 1; i++) {
		k = i;
		for (j = i + 1; j < flag->Successfulnumber; j++){
			temp = strcmp(student[j].name, student[k].name);
			if (mode == 4)temp = -temp;
			if ( temp< 0)k = j;
		}
		if (k != i)Swap(&student[k],&student[i]);
	}
	flag->sortflag = 10+mode;//排序完成后标记当前排序状态
}

void SortScore(FLAG *flag, STU student[], int mode) {
	int i = 0, j = 0, k = 0;
	int temp;

	//如果已排序则不必重复排序
	if (flag->sortflag == mode)return;
	for (i = 0; i < flag->Successfulnumber - 1; i++) {
		k = i;
		for (j = i + 1; j < flag->Successfulnumber; j++) {
			temp = (student[j].totalscore<student[k].totalscore);
			if (mode == 4)temp = !temp;
			if (temp)k = j;
		}
		if (k != i)Swap(&student[k], &student[i]);
	}
	flag->sortflag = mode;//排序完成则标记当前排序状态
}

void SortNumber(FLAG *flag, STU student[], int mode) {
	int i = 0, j = 0, k = 0;
	int temp;

	//如果已排序则无需重复排序
	if (flag->sortflag == 20+mode)return;
	for (i = 0; i < flag->Successfulnumber - 1; i++) {
		k = i;
		for (j = i + 1; j < flag->Successfulnumber; j++) {
			temp = (student[j].number<student[k].number);
			if (mode == 4)temp = !temp;
			if (temp)k = j;
		}
		if (k != i)Swap(&student[k], &student[i]);
	}
	flag->sortflag = 20+mode;//排序完成后标记排序状态
}

int AnalyzeOrder(char ml[], int x) {
	const char ML1[10][5] = { "new","del","re","sch","ls","rd","wr","help","menu","exit" };
	const char ML2[5][7] = { "score","name","number","asc","desc" };
	int i;//定义用于存储有效命令的数组

	if (x == 1) {
		for (i = 0; i < 10;i++)if (strcmp(ml, ML1[i]) == 0)return i;	
	}
	else if (x == 2) {
		for (i = 0; i < 5;i++)if (strcmp(ml, ML2[i]) == 0)return i;
	}
	return -1;//匹配不成功则返回-1
}

void ListStudent(FLAG*flag, STU student[]) {
	char ml1[7] = { 0 }, ml2[5] = { 0 };
	int n = -1, m = -1;

	//读取命令并检查
	if (scanf("%s %s", ml1, ml2) != 2) {
		printf("'ls %s %s'不是完整命令或不是有效命令!\n", ml1, ml2);
		return;
	}

	n = AnalyzeOrder(ml1, 2);
	m = AnalyzeOrder(ml2, 2);
	if ( m == 3 || m == 4)
	{//根据命令排序,出错则输出错误信息
		switch (n)
		{
		case 0:SortScore(flag, student, m); break;
		case 1:SortName(flag, student, m); break;
		case 2:SortNumber(flag, student, m); break;
		default:printf("'%s %s'不是有效的命令参数!\n", ml1, ml2);
			break;
		}
		PrintStudent(flag, student,-1);
	}
	else { //出错则输出错误信息
		printf("'%s %s'不是有效的命令参数!\n",ml1,ml2);
		return;
	}
}

int SearchStudent(FLAG*flag, STU student[], int x) {
	char ml[7] = { 0 }, name[NAME] = {0};
	long number = 0;
	int i=0, n = flag->Successfulnumber;

	//未知检索条件则先读取命令分析检索条件
	if (x == -1) {
		scanf("%6s", ml);
		x = AnalyzeOrder(ml, 2);
	}
	if (x == -1) printf("'sch %s'不是有效的命令,请重新输入!\n", ml);

	if (x == 1) { //检索姓名并返回下标
		printf("请输入指定学生的姓名:");
		scanf("%14s", name);
		for (i = 0; i < n; i++) {
			if (strcmp(name, student[i].name) == 0)
				return i;
		}
	}else if (x == 2) { //检索学号并返回下标
		printf("请输入指定学生的学号:");
		scanf("%ld", &number);
		for (i = 0; i <n; i++) {
			if (number == student[i].number)
				return i;
		}
	}

	puts("未检索到该学生信息!");
	return -1;//未检索到返回-1
}

void DeleteStudent(FLAG *flag, STU student[]) {
	char ml[7] = { 0 };
	int n=-1,x=-1,i=flag->Successfulnumber-1;

	//从缓冲区读取指令并错误则报错
	if (!scanf("%6s", ml))
	{
		puts("无效命令,请重新输入\n");
		return;
	}

	n = AnalyzeOrder(ml, 2);
	if(n==1||n==2)x = SearchStudent(flag,student,n);
	else printf("'del %s'不是有效指令,请重新输入",ml);

	if (x != -1) {//检索到学生信息则用最后一条信息覆盖该信息
		if (x != i) { 
			student[x] = student[i];
			flag->sortflag = -1;//信息变动需要重新排序
		}
		flag->Successfulnumber--;//已登记人数减一
	}
}

void ViewHelp(void) {
	char ml2[5];

	scanf("%4s",ml2);
	switch (AnalyzeOrder(ml2,1))//分析指令分别输出对应详细帮助
	{
	case 0:puts("new n命令用于新建n(<30人)个学生信息,输入该指令将引导您新建学生信息"); break;
	case 1:puts("del name/numble命令用于按姓名/学号索引学生信息并删除"); break;
	case 2:puts("re name/numble命令用于按姓名/学号检索学生信息并修改"); break;
	case 3:puts("sch name/numble命令用于按姓名/学号检索学生信息"); break;
	case 4:puts("ls name/numble/score asc/desc命令由三部分组成,\n表示按照姓名/学号/总分进行升/降序排序后打印成绩单"); break;
	case 5:puts("rd xxx用于读取成绩存档,xxx为文件地址和文件名"); break;
	case 6:puts("wr xxx用于导出成绩存档文件,xxx为文件地址和文件名"); break;
	case 7:puts("help xx命令用于查看xx命令的详细使用帮助"); break;
	case 8:puts("menu 命令用于查看命令菜单"); break;
	case 9:puts("exit 命令用于保存并退出程序,默认保存的在程序同目录下student.txt文件中"); break;
	default:
		printf("' %s'不是有效命令，请输入正确命令",ml2);
		break;
	}
}

void PrintStudent(FLAG *flag, STU student[],int x) {
	int i = 0,j=0;

	//打印表头
	printf("\n姓名\t学号");
	for (i = 0; i < flag->courseN; i++)printf("\t科目%d", i + 1);
	printf("\t总分\t平均分");

	if (x != -1) {//输出指定学生信息
		printf("\n%s\t%ld", student[x].name, student[x].number);
		for (i = 0; i <flag->courseN; i++)
			printf("\t%d", student[x].score[i]);
		printf("\t%d\t%.1f",student[x].totalscore,student[x].averscore);
	}
	else for (i = 0; i < flag->Successfulnumber; i++) {
		//输出全部 学生信息
		printf("\n%s\t%ld", student[i].name, student[i].number);
		for (j = 0; j < flag->courseN; j++)
			printf("\t%d", student[i].score[j]);
		printf("\t%d\t%.1f", student[i].totalscore, student[i].averscore);
	}
}