#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#define COURSE_NUM 6
#define STU_NUM 30
#define MAX_LEN 10
typedef struct student
{
    long num;
    char name[MAX_LEN];
    float score[COURSE_NUM];
    float sum;
    float aver;
    struct student * next;
}STU;
int Login(void);
int Menu(void);
STU * ReadScore(STU *head,int n,int m,char coursename[][MAX_LEN],int maxscore[]);
STU * AverSumofEveryStudent(STU *head,int n,int m);
void AverSumofEveryCourse(STU *head,int n,int m,char coursename[][MAX_LEN]);
STU * SortbyScore(STU *head,int n,int m,int (*compare)(float a,float b));
int Ascending(float a,float b);
int Descending(float a,float b);
void SwapFloat(float *x,float *y);
void SwapLong(long *x,long *y);
void SwapChar(char x[],char y[]);
STU * AsSortbyNum(STU *head,int n,int m);
STU * SortbyName(STU *head,int n,int m);
void SearchbyNum(STU *head,int n,int m,char coursename[][MAX_LEN]);
void SearchbyName(STU *head,int n,int m,char coursename[][MAX_LEN]);
void StatisticAnalysis(STU *head,int n,int m,char coursename[][MAX_LEN],int max[]);
void PrintScore(STU *head,int n,int m,char coursename[][MAX_LEN]);
void AverSumofEveryStudent2(STU *head,int n,int m);/*专门写一个函数用于计算平均值和总分只是不向屏幕输出*/
void WritetoFile(STU *head,int n,int m,char coursename[][MAX_LEN],int max[]);
STU * ReadfromFlie(int *n,int *m,char coursename[][MAX_LEN],int max[]);
int DeleteMemory(STU *head);
STU *AppendEmptyNode(STU *head,int n,int m);
STU *DeleteNode(STU *head,int *n);
STU *Adddata(STU *head,int m,char coursename[][MAX_LEN],int *n);

int main()
{
    int i,n,m,t,l,item,iscls,maxscore[COURSE_NUM];
    int canlogin,logintimes;
    STU * head  = NULL;
    char coursename[COURSE_NUM][MAX_LEN];
    for(logintimes = 0;logintimes < 3;logintimes++)
    {
        canlogin = Login();
        if(canlogin == 1)
        {
            printf("Logining Please wait!\n");
            for(i = 0;i < 1e9;i++);//通过这种没有内容的循环拖延时间模拟加载的过程
            printf("Welcome to our program!\n");
            for(i = 0;i < 1e9;i++);//这样看着舒服
            do
            {
                fflush(stdin);
                printf("Input student number(n <= %d):",STU_NUM);
                t = scanf("%d",&n);
                printf("Input course number(m <= %d)\n",COURSE_NUM);
                l = scanf("%d",&m);
            }while(n <= 0 || m <= 0 || n > STU_NUM || m > COURSE_NUM || t != 1 || l != 1);/*输入学生的人数n以及科目的总数m并且对输入的数据加加以检查*/
            while(1)
            {
                item = Menu();
                switch(item)
                {
                case 1:
                    head = ReadScore(head,n,m,coursename,maxscore);
                    break;
                case 2:
                    AverSumofEveryCourse(head,n,m,coursename);
                    break;
                case 3:
                    head = AverSumofEveryStudent(head,n,m);
                    break;
                case 4:
                    SortbyScore(head,n,m,Descending);//将Descending函数的地址传给函数指针
                    printf("\nSort in descending order by score:\n");
                    PrintScore(head,n,m,coursename);
                    break;
                case 5:
                    SortbyScore(head,n,m,Ascending);//将Aescending函数的地址传给函数指针
                    printf("\nSort in ascending order by score:\n");
                    PrintScore(head,n,m,coursename);
                    break;
                case 6:
                    AsSortbyNum(head,n,m);
                    printf("\nSort in ascending order by number:\n");
                    PrintScore(head,n,m,coursename);
                    break;
                case 7:
                    head = SortbyName(head,n,m);
                    printf("\nSort in dictionary number by name:\n");
                    PrintScore(head,n,m,coursename);
                    break;
                case 8:
                    SearchbyNum(head,n,m,coursename);
                    break;
                case 9:
                    SearchbyName(head,n,m,coursename);
                    break;
                case 10:
                    StatisticAnalysis(head,n,m,coursename,maxscore);
                    break;
                case 11:
                    PrintScore(head,n,m,coursename);
                    break;
                case 12:
                    WritetoFile(head,n,m,coursename,maxscore);
                    break;
                case 13:
                    head = ReadfromFlie(&n,&m,coursename,maxscore);
                    PrintScore(head,n,m,coursename);
                    break;
                case 14:
                    head = DeleteNode(head,&n);
                    break;
                case 15:
                    head = Adddata(head,m,coursename,&n);
                    break;
                case 0:
                    printf("Exiting Please wait!\n");
                    for(i = 0;i < 1e9;i++);//延时循环模拟退出的过程
                    printf("End of program!Look forward to seeing you again!\n");
                    i = DeleteMemory(head);
                    if(i == 1)
                        printf("Memory has been deleted!\n");
                    exit(0);
                default:
                    printf("Input arrow!\n");
                }
            }
            printf("\nInput 1 if you want to clear screen!\n");
            scanf("%d",&iscls);//用于保存用户的回答
            if(iscls == 1)
            {
            system("cls"); //调用函数清屏，使屏幕简单
            }
        }
        else if(logintimes < 2)
        {
            printf("Wrong name!Please try again!\n");
        }
    }
    printf("Wrong!You have tried three times!Program closed!\n");
    return 0;
}

/*函数接口：无
  函数功能：模拟用户登陆
  函数返回值：登陆成功为1否则为0*/
int Login(void)
{
    char name[7][MAX_LEN] = {"张艳","付勇","曹庭正","丁勇义","何祖元","陈义群","聂晨晞"};
    char name2[MAX_LEN];
    int i;
    printf("Name:");
    gets(name2);
    for(i = 0;i <7;i++)
    {
        if(strcmp(name2,name[i]) == 0)
            return 1;
    }
    return 0;
}

/*函数接口：无
  函数功能：显示菜单供用户选择相应的功能并且在第一次输入时限制选择1
  函数返回值：返回用户选择的代号给主函数*/
int Menu(void)
{
    int itemSelected,k;
    static int i = 1;
    printf("\nManagement for students' score V6.0\n");
    printf("1.Input record.\n");
    printf("2.Calculate total and average score of every course.\n");
    printf("3.Calculate total and average score of every student.\n");
    printf("4.Sort in descending order by score.\n");
    printf("5.Sort in ascending order by score.\n");
    printf("6.Sort in ascending order by number.\n");
    printf("7.Sort in dictionary order by name.\n");
    printf("8.Search by number.\n");
    printf("9.Search by name\n");
    printf("10.Statistic analysis.\n");
    printf("11.List record.\n");
    printf("12.Write to a file.\n");
    printf("13.Read from a file.\n");
    printf("14.Delete data\n");
    printf("15.Add data\n");
    printf("0.Exit!\n");
    if(i == 1)
    {
        do
        {
            fflush(stdin);
            printf("Please input 1 or 13 since this is your first choice:");
            k = scanf(" %d",&itemSelected);
        }while((itemSelected != 1 && itemSelected != 13)|| k != 1);
        i++;
    }
    else
    {
        do
        {
            fflush(stdin);
            printf("Please input your choice:");
            k = scanf("%d",&itemSelected);
        }while(k != 1);
    }
    return itemSelected;
}

/*函数接口：链表的头指针、课程名、学生数n、课程数m
  函数功能：输入学生的成绩、名字、学号、输入课程名
  函数返回值：链表头指针*/
STU * ReadScore(STU *head,int n,int m,char coursename[][MAX_LEN],int maxscore[])
{
    STU *p = NULL,*pr = head;
    int i,j;
    printf("Please input %d courses' names and their total points:\n",m);
    for(j = 0;j < m;j++)
    {
        scanf("%s%*c%d",coursename[j],&maxscore[j]);
    }
    for(i = 0;i < n;i++)
    {
        p = (STU *) malloc(sizeof(STU));
        if(p == NULL)
        {
            printf("Arrow!No enough memory!");
            exit(0);
        }
        else
        {
            if(head == NULL)
            {
                head = p;
                pr = p;
                p -> next =  NULL;
            }
            else
            {
                pr->next = p;
                pr = p;
                p->next = NULL;
            }
        }
        printf("Input student%d's ID,name:",i+1);
        scanf("%ld%*c%s",&p->num,p->name);
        for(j = 0;j < m;j++)
        {
            do
            {
                printf("Input his/her score for %s",coursename[j]);
                scanf("%f",&p->score[j]);
            }while(p->score[j] < 0 || p->score[j] > maxscore[j]);
        }
        p->sum = 0;
        p->aver = 0;
    }
    return head;
}

/*函数接口：链表头指针、学生数、课程数、课程名字
  函数功能：统计各课程的平均分和总分
  函数返回值：无*/
void AverSumofEveryCourse(STU *head,int n,int m,char coursename[][MAX_LEN])
{
    STU *p = head;
    int j;
    float sum[m],aver[m];
    for(j = 0;j < m;j++)
    {
        sum[j] = 0;
        while(p != NULL)
        {
            sum[j] = sum[j] + p->score[j];
            p = p->next;
        }
        aver[j]  = sum[j] / n;
        if(p == NULL)
            p = head;
    }
    for(j = 0;j < m;j++)
    {
        printf("%s:sum = %.2f,aver = %.2f\n",coursename[j],sum[j],aver[j]);

    }
}

/*函数接口：链表头指针、学生数n，课程数m
  函数功能：统计学生的平均分和总分
  函数返回值：链表头指针*/
STU * AverSumofEveryStudent(STU *head,int n,int m)
{
    STU *p = head;
    int j;
    while(p!=NULL)
    {
        p->sum = 0;
        for(j = 0;j < m;j++)
        {
            p->sum = p->sum + p->score[j];
        }
        p->aver = p->sum / m;
        p=p->next;
    }
    p = head;
    while(p!=NULL)
    {
        printf("%ld\t%s\tsum=%.2f\taver=%.2f\t\n",p->num,p->name,p->sum,p->aver);
        p=p->next;
    }
    return head;
}

/*函数接口：链表的头指针、学生人数n、课程数m、函数指针compair
  函数功能：根据compair的指向实现升或者降序排列（运用交换法）
  函数返回值：；链表的头指针*/
STU * SortbyScore(STU *head,int n,int m,int (*compare)(float a,float b))
{
    STU *p = head,*pr = NULL;
    int j;
    if(p->sum == 0)
        AverSumofEveryStudent2(head,n,m);//防止一输完数据就排序没有平均分和总分的情况
    while(p != NULL)
    {
        pr = p->next;
        while(pr != NULL)
        {
            if((*compare)(p->sum,pr->sum))
            {
                SwapLong(&p->num,&pr->num);//交换学号
                SwapChar(p->name,pr->name);//交换姓名
                for(j = 0;j < m;j++)
                {
                    SwapFloat(&p->score[j],&pr->score[j]);
                }//交换成绩
                SwapFloat(&p->sum,&pr->sum);//交换总分
                SwapFloat(&p->aver,&pr->aver);//交换平均分
            }
            pr = pr -> next;
        }
        p = p->next;
    }
    return head;
}

/*若为升序排列*/
int Ascending(float a,float b)
{
    return b < a;
}

/*若为降序排列*/
int Descending(float a,float b)
{
    return b > a;
}

/*函数接口：指向float型变量的两个指针x，y
  函数功能：通过解引用交换两个数
  函数返回值：无*/
void SwapFloat(float *x,float *y)
{
    float temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/*函数接口：指向long型变量的两个指针x，y
  函数功能：通过解引用交换两个数
  函数返回值：无*/
void SwapLong(long *x,long *y)
{
    long temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/*函数接口：两个存储有字符串的字符数组
  函数功能：通过字符串操作函数交换两个数
  函数返回值：无*/
void SwapChar(char x[],char y[])
{
    char temp[MAX_LEN];
    strcpy(temp,x);
    strcpy(x,y);
    strcpy(y,temp);
}

/*函数接口：链表的头指针，学生人数n，课程数m
  函数功能：对学号由小到大排列(选择法排序)
  函数返回值：链表的头指针*/
STU * AsSortbyNum(STU *head,int n,int m)
{
    STU *p = head,*pr = NULL,*pt = NULL;
    int j;
    if(p->sum == 0)
        AverSumofEveryStudent2(head,n,m);//防止一输完数据就排序没有平均分和总分的情况
    while(p != NULL)
    {
        pr = p->next;
        pt = p;
        while(pr != NULL)
        {
            if(pr->num < pt->num)
            {
                pt = pr;
            }
            pr = pr -> next;
        }
        if(pt != p)
        {
            SwapLong(&pt->num,&p->num);//交换学号
            SwapChar(pt->name,p->name);//交换姓名
            for(j = 0;j < m;j++)
            {
                SwapFloat(&pt->score[j],&p->score[j]);
            }//交换成绩
            SwapFloat(&pt->sum,&p->sum);//交换总分
            SwapFloat(&pt->aver,&p->aver);//交换平均分
        }
        p = p->next;
    }
    return head;
}

/*函数接口：链表头指针、学生人数、课程数
  函数功能：按照字典序对学生姓名进行排列
  函数返回值：链表头指针*/
STU * SortbyName(STU *head,int n,int m)
{
    STU *p = head,*pr = NULL;
    int j;
    while(p != NULL)
    {
        pr = p->next;
        while(pr != NULL)
        {
            if((strcmp(p->name,pr->name) > 0))
               {
                   SwapLong(&p->num,&pr->num);
                   SwapChar(p->name,pr->name);
                   for(j = 0;j < m;j++)
                   {
                       SwapFloat(&p->score[j],&pr->score[j]);
                   }
                   SwapFloat(&p->sum,&pr->sum);
                   SwapFloat(&p->aver,&p->aver);
               }
               pr = pr -> next;
        }
        p = p -> next;
    }
    return head;
}

/*函数接口：链表的头指针，课程数、课程名字
  函数功能：按照学号查找（遍历法）
  函数返回值：无*/
void SearchbyNum(STU *head,int n,int m,char coursename[][MAX_LEN])
{
    long target;
    STU *p = head;
    int j;
    printf("Please input the number you want to search:");
    scanf("%ld",&target);
    if(p->sum == 0)
        AverSumofEveryStudent2(head,n,m);//防止一输完数据就查找没有平均分和总分的情况
    while(p != NULL)
    {
        if(p->num == target)
        {
            printf("%ld\t%s\t",p->num,p->name);
            for(j = 0;j < m;j++)
            {
                printf("%s:%.2f\t",coursename[j],p->score[j]);
            }
            printf("Sum:%.2f\tAver:%.2f\n",p->sum,p->aver);
            return;
        }
        p = p->next;
    }
    printf("Sorry,%ld has not been found!\n",target);
}
/*函数接口：链表的头指针，课程数m，课程名称
  函数功能：对学生的姓名进行查找
  函数返回值：无*/
void SearchbyName(STU *head,int n,int m,char coursename[][MAX_LEN])
{
    char target[MAX_LEN];
    STU *p = head;
    int j;
    if(p->sum == 0)
        AverSumofEveryStudent2(head,n,m);//防止一输完数据就查找没有平均分和总分的情况
    printf("Input the name you want to search:\n");
    scanf("%s",target);
    while(p != NULL)
    {
        if((strcmp(p->name,target)) == 0)
        {
            printf("%ld\t%s\t",p->num,p->name);
            for(j = 0;j < m;j++)
            {
                printf("%s:%.2f\t",coursename[j],p->score[j]);
            }
            printf("Sum:%.2f\tAver:%.2f\n",p->sum,p->aver);
            return;
        }
        p = p->next;
    }
    printf("Sorry %s has not been found!",target);
}

/*函数接口：链表头指针、学生人数、课程数、课程名称
  函数功能：打印学生信息
  函数返回值：无*/
void PrintScore(STU *head,int n,int m,char coursename[][MAX_LEN])
{
    STU *p = head;
    int j;
    if(p->sum == 0)
        AverSumofEveryStudent2(head,n,m);//防止一输完数据就打印没有平均分和总分的情况
    while(p != NULL)
    {
        printf("%ld\t%s\t",p->num,p->name);
        for(j = 0;j < m;j++)
        {
            printf("%s:%.2f\t",coursename[j],p->score[j]);
        }
        printf("Sum:%.2f\tAver:%.2f\n",p->sum,p->aver);
        p = p -> next;
    }
}

/*函数接口：链表的头指针，课程数m，课程的名称，各门课程的最高分
  函数功能对每门课进行成绩分析:统计成绩从总分的0.6，0.7，0.8，0.9，1.0各个分数段的成绩段的人数以及半分比
  函数返回值：无*/
void StatisticAnalysis(STU *head,int n,int m,char coursename[][MAX_LEN],int max[])
{
    int i,j,t[6];
    STU *p = head;
    for(j = 0;j < m;j++)
    {
        memset(t,0,sizeof(t));
        while(p != NULL)
        {
            if(p->score[j] >= 0 && p->score[j] < max[j] * 0.6)
                t[0]++;
            else if(p->score[j] < max[j] * 0.7)
                t[1]++;
            else if(p->score[j] < max[j] * 0.8)
                t[2]++;
            else if(p->score[j] < max[j] * 0.9)
                t[3]++;
            else if(p->score[j] < max[j] * 1.0)
                t[4]++;
            else if(fabs(p->score[j] - max[j]) < 1e-7)//两个浮点数判断是否相等
                t[5]++;
            p = p->next;
        }
        printf("%s:\n",coursename[j]);
        for(i = 0;i < 6;i++)
        {
            if(i == 0)
                printf("<%.0f\t%d\t%.2f%%\n",(float)max[j] * 0.6,t[i],(float)t[i]/n*100);
            else if(i == 5)
                printf("%.0f\t%d\t%.2f%%\n",(float)max[j],t[i],(float)t[i]/n*100);
            else
                printf("%.0f--%.0f\t%d\t%.2f%%\n",(float)max[j] * (i + 5) * 0.1,(float)max[j] * (i + 6) * 0.1,t[i],(float)t[i]/n*100);
        }
        if(p == NULL)
            p = head;
    }
}

/*函数接口：链表的头指针，学生数n，课程数m，课程的名字
  函数功能：将学生的信息写入文档当中
  函数返回值：无*/
void WritetoFile(STU *head,int n,int m,char coursename[][MAX_LEN],int max[])
{
    FILE *fp;
    int j;
    STU *p = head;
    if(p->sum == 0)
        AverSumofEveryStudent2(head,n,m);//防止一输完数据就写入文档没有平均分和总分的情况
    if((fp = fopen("student.txt","w")) == NULL)
    {
        printf("Fail to open student.txt!\n");
        exit(0);
    }
    fprintf(fp,"StudentNumber: %d Coursenumber: %d\n",n,m);
    while(p != NULL)
    {
        fprintf(fp,"%10ld%10s",p->num,p->name);
        for(j = 0;j < m;j++)
        {
            fprintf(fp,"%10s : %.2f",coursename[j],p->score[j]);
        }
        fprintf(fp,"\tsum=%.2f\taver=%.2f\n",p->sum,p->aver);
        p = p->next;
    }
    for(j = 0;j < m;j++)
    {
        fprintf(fp,"max %s %d\n",coursename[j],max[j]);
    }
    fclose(fp);
    printf("Writing to a file has succeeded!\n");
}

/*函数接口：一个链表的头指针，指向学生人数的指针，指向课程数的指针，读取的课程名
  函数功能：从一个文档中读入数据
  函数返回值：链表的头指针*/
STU * ReadfromFlie(int *n,int *m,char coursename[][MAX_LEN],int max[])
{
    FILE *fp;
    STU *head = NULL;
    int j;
    STU *p = NULL;
    if((fp = fopen("student.txt","r")) == NULL)
    {
        printf("Fail to open student.txt!\n");
        exit(0);
    }
    fscanf(fp,"StudentNumber: %d Coursenumber: %d",n,m);//从文件中读入学生人数和课程门数
    head = AppendEmptyNode(head,*n,*m);//创建一个数据域是空的的链表等待被读入数据
    p = head;
    while(p != NULL)
    {
        fscanf(fp,"%10ld%10s",&p->num,p->name);
        for(j = 0;j < *m;j++)
        {
            fscanf(fp,"%10s : %f",coursename[j],&p->score[j]);
        }
        fscanf(fp,"\tsum=%f\taver=%f\n",&p->sum,&p->aver);
        p = p->next;
    }
    for(j = 0;j < *m;j++)
    {
        fscanf(fp,"max %*s%d\n",&max[j]);
    }
    printf("Reading from file has succeeded!\n");
    fclose(fp);
    return head;
}

/*函数接口：链表头指针、学生数n，课程数m
  函数功能：统计学生的平均分和总分
  函数返回值：无*/
void AverSumofEveryStudent2(STU *head,int n,int m)
{
    STU *p = head;
    int j;
    while(p!=NULL)
    {
        p->sum = 0;
        for(j = 0;j < m;j++)
        {
            p->sum = p->sum + p->score[j];
        }
        p->aver = p->sum / m;
        p=p->next;
    }
}

/*函数接口：链表的头指针
  函数功能：清除内存
  函数返回值：无*/
int DeleteMemory(STU* head)
{
   STU *p = head,*pr = NULL;
   while(p != NULL)
   {
       pr = p;
       p = p->next;
       free(pr);
   }
   return 1;
}

/*函数接口：链表的头指针，学生人数
  函数功能：建立一个数据域是空的的链表
  函数返回值：链表的头指针*/
STU *AppendEmptyNode(STU *head,int n,int m)
{
    STU *p = NULL,*pr = head;
    int i,j;
    for(i = 0;i < n;i++)
    {
        p = (STU *)malloc(sizeof(STU));
        if(p == NULL)
        {
            printf("No enough memory!\n");
            exit(0);
        }
        if(head == NULL)
        {
            head = p;
            pr = p;
            pr->next = NULL;
        }
        else
        {
            pr->next = p;
            pr = p;
            p->next = NULL;
        }
        p->aver = 0;
        p->num = 0;
        for(j = 0;j < m;j++)
        {
            p->score[j]=0;
        }
        p->sum=0;
    }
    return head;
}

/*函数接口：链表的头指针,指向学生人数的指针n
  函数功能：根据学号删除一个同学的数据
  函数返回值：链表的头指针*/
STU *DeleteNode(STU *head,int *n)
{
    long num1,num2;
    STU *p = head,*pr = head;
    printf("Input the number you want to delete\n");
    scanf("%ld",&num1);
    printf("Please input again to make sure\n");
    scanf("%ld",&num2);
    if(num1 == num2)
    {
        while(p->next != NULL &&p ->num !=num1)/*未找到且未到表尾*/
        {
            pr = p;/*在pr中保存当前节点的指针*/
            p = p->next;/*p指向下一个节点*/
        }
        if(num1 == p->num)
        {
           if(p == head)    /*若待删除的是头节点*/
           {
               head = p->next;/*让头指针指向待删除的下一个节点*/
           }
           else /*若待删节点不是头节点*/
           {
               pr->next = p->next;/*让前一节点的指针域指向待删节点的下一节点*/
           }
           free(p);
           printf("%ld has been deleted!\n",num1);
           *n = *n - 1;//人数减一
        }
        else
        {
            printf("%ld has not been found!",num1);
        }
    }
    return head;
}

/*函数接口：链表的头指针,课程数，课程名字，指向人数的指针n
  函数功能：插入一个学生的信息
  函数返回值：链表的头指针*/
STU *Adddata(STU *head,int m,char coursename[][MAX_LEN],int *n)
{
    STU *pr = head,*p = head,*temp = NULL;
    int j;
    p = (STU *)malloc(sizeof(STU));
    if(p == NULL)
    {
        printf("No enough memory!\n");
        exit(0);
    }
    p->next = NULL;
    printf("Input the new student's ID and name:");
    scanf("%ld%*c%s",&p->num,p->name);
    for(j = 0;j < m;j++)
    {
        printf("Input the new student's score for %s",coursename[j]);
        scanf("%f",&p->score[j]);
    }
    if(head == NULL)
    {
        head = p;
    }
    else
    {
        while(pr->num < p->num && pr->next != NULL) //若未找到带插入节点且位置未到表尾
        {
            temp = pr;
            pr = pr->next;
        }
        if(pr->num >= p->num)/*若待插入的节点不在表尾*/
        {
            if(pr == head)/*若在头节点前插入新节点*/
            {
                p->next = head;/*将新节点的指针域指向原链表的头节点*/
                head = p;/*head指向新的头节点*/
            }
            else
            {
                pr = temp; /*让pr指向那个刚好比待插入节点num小的那个节点*/
                p->next = pr->next;/*让新节点的指针域指向下一节点*/
                pr->next = p;/*让前一节点的指针域指向新节点*/
            }
        }
        else//若待插入的节点在表尾
        {
            pr->next = p;
        }
    }
    *n = *n + 1;//人数加一
    return head;
}
