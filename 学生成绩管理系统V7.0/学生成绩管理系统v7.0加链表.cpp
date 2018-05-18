/*本程序特色：算学分绩，按学分绩排序，查找成绩区间上的同学*/ 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define   MAX_LEN  10                	   /* 字符串最大长度 */
#define   STU_NUM 30                       /* 最多的学生人数 */
#define   COURSE_NUM 6                     /* 最多的考试科目数 */
typedef struct Class
{
	float point;
}CLASS;

typedef struct student
{
    long num;	/* 每个学生的学号 */
    char name[MAX_LEN];            	/* 每个学生的姓名 */
    float score[COURSE_NUM];	/* 每个学生COURSE_NUM门功课的成绩 */
    float sum;                       /* 每个学生的总成绩 */
    float aver;  
    float creditgrade;
	struct student *next;                 /* 每个学生的平均成绩 */
}STU;

STU *Delete(STU *head);
int   Menu(void); 
int   Ascending(float a, float b);
int   Descending(float a, float b);
void swap(STU *stu1, STU *stu2);
void  ReadScore(STU *stu, int *m);
void  AverSumofEveryStudent(STU *stu, int m);
void  AverSumofEveryCourse(STU *stu, int m,int n);
void  SortbyScore(STU *stu,int (*compare)(float a,float b));
void  AsSortbyNum(STU *stu);
void  SortbyName(STU *stu);
void  SearchbyNum(STU *stu,int m);
void  SearchbyName(STU *stu,int m);
void  StatisticAnalysis(STU *stu,int m);
void  PrintScore(STU *stu, int m);
void  WritetoFile(STU *stu,int n,int m);
void  ReadfromFile(STU *stu,int *n,int *m);
void  distribute(STU **stu, int n);
void SearchInaInterval(STU *stu,int m);
void CreditGrade(STU *stu,int m);
 
 /*主函数*/ 
 int main()
 {
 	int ch;
 	int n=0,m=0;
 	STU *stu;
 	do
 	{
 		printf("Input student number(n<30):\n");
 		scanf("%d",&n);
 }while(!(n<30&&n>0));
 	distribute(&stu,n); 
 	while(1)
 	{
	 	ch=Menu();
 		switch(ch)
 		{
 			case 1:
			ReadScore(stu,&m);
 			break;
 			case 2:
			AverSumofEveryCourse(stu,m,n);
 			break;
 			case 3:
			AverSumofEveryStudent(stu, m);
 			break;
 			case 4:
			SortbyScore(stu,Descending);
 			printf("Sort in descending order by score:\n");
 			PrintScore(stu,m);
 			break;
 			case 5:
			SortbyScore(stu,Ascending);
 			printf("Sort in ascending order by score:\n");
 			PrintScore(stu,m);
 			break;
 			case 6:
			AsSortbyNum(stu);
 			printf("Sort in ascending order by number:\n");
 			PrintScore(stu,m);
 			break;
 			case 7:
			SortbyName(stu);
			printf("Sort in dictionary order by name:\n");
			PrintScore(stu,m);
			break;
 			case 8:
			SearchbyNum(stu,m);
 			break;
 			case 9:
			SearchbyName(stu,m);
 			break;
 			case 10:
			StatisticAnalysis(stu,m);
 			break;
 			case 11:
			PrintScore(stu,m);
 			break;
 			case 12:
			WritetoFile(stu,n,m);
 			break;
 			case 13:
			ReadfromFile( stu, &n, &m);
 			break;
 			case 14:
 			stu=Delete(stu);
 			break;
 			case 15:
 			SearchInaInterval(stu,m);
 			break;
 			case 16:
 			CreditGrade(stu,m);
 			break;
 			case 0:
			printf("End of program!\n");
 			exit(0);
 			default:
			printf("Input error!\n");
		 } 
	 }  
	 return 0;
 }
 /*打印菜单*/ 
 int   Menu(void)
 {
 	 int itemSelected;
	 printf("Management for Students' scores\n");
	 printf("1.Input record\n");
	 printf("2.Caculate total and average score and credit grade of every course\n");
	 printf("3.Caculate total and average score of every student\n");
	 printf("4.Sort in descending order by score\n");
	 printf("5.Sort in ascending order by score\n");
	 printf("6.Sort in ascending order by number\n");
	 printf("7.Sort in dictionary order by name\n");
	 printf("8.Search by number\n");
	 printf("9.Search by name\n");
	 printf("10.Statistic analysis\n");
	 printf("11.List record\n");
	 printf("12.Write to a file\n");
	 printf("13.Read from a file\n");
	 printf("14.Delete a student\n");
	 printf("15.Search student in a interval of score\n");
	 printf("16.Calculate the credit grade of every student\n");
	 printf("0.Exit\n");
	 printf("Please Input your choice:\n");
	 scanf("%d",&itemSelected);
	 return itemSelected;
 } 
/*交换数据*/ 
 void swap(STU *stu1, STU *stu2)
{
	STU temp;
	temp = *stu1;
	*stu1 = *stu2;
	*stu2 = temp;
	temp.next=stu1->next;
	stu1->next=stu2->next;
	stu2->next=temp.next;
}
/*申请内存*/ 
 void distribute(STU **stu, int n)
{
	int i;
	*stu=(STU *)malloc(sizeof(STU));
	STU *stutail=*stu;
	for(i=1;i<n;i++)
	{
		stutail->next=(STU *)malloc(sizeof(STU));
		stutail=stutail->next;
	}
	stutail->next=NULL;
}
/*读入数据*/ 
void  ReadScore(STU *stu,int *m)
{
	int j; 
	do{
 		printf("Input course number(m<=%d):\n",COURSE_NUM);
 		scanf("%d",m);
	 }while(!(*m<=6&&*m>0));
	printf("Input student's ID, name and score:\n"); 
	for( ;stu!=NULL;stu=stu->next)
	{
		scanf("%ld%s",&stu->num,stu->name);
		for(j=0;j<*m;j++)
		scanf("%f",&stu->score[j]);
	}
}
/*计算每个学生得平均成绩*/ 
void  AverSumofEveryStudent(STU *stu, int m)
{
	int j;
	for( ;stu!=NULL;stu=stu->next)
	{
		stu->sum=0;
		for(j=0;j<m;j++)
		{
			stu->sum+=stu->score[j];
		}
		stu->aver=m>0?stu->sum/m:-1;
		printf("student %d: sum=%.0f,aver=%.0f\n",stu->num,stu->sum,stu->aver);
	}
}
/*计算每门课得平均成绩*/ 
void  AverSumofEveryCourse(STU *stu, int m,int n)
{
	int j;
	STU *blank;
	float sum[COURSE_NUM],aver[COURSE_NUM];
	for(j=0;j<m;j++)
	{
		blank=stu;
		sum[j]=0;
		for(;blank!=NULL;blank=blank->next)
		{
			sum[j]=sum[j]+blank->score[j];
		}
		aver[j]= n>0 ? sum[j]/n: -1;
		printf("course %d:sum=%.0f,aver=%.0f\n",j+1,sum[j],aver[j]);
	}
}
/*按成绩排序*/ 
void  SortbyScore(STU *stu,int (*compare)(float a,float b))
{
	STU *i,*j,*temp;
	for(i=stu;i->next!=NULL;i=i->next)
	{
		temp=i;
		for(j=i->next;j!=NULL;j=j->next)
		{
			if(compare(j->sum,temp->sum))
			temp=j;
		}
		if(temp!=i)
		{
			swap(i,temp);
		}
	}
}
/*升序*/ 
int   Ascending(float a, float b)
{
	return a<b;
}
/*降序*/ 
int   Descending(float a, float b)
{
	return a>b;
}
/*按学号升序排序*/ 
void  AsSortbyNum(STU *stu)
{
	STU *i,*j,*temp;
	for(i=stu;i->next!=NULL;i=i->next)
	{
		temp=i;
		for(j=i->next;j!=NULL;j=j->next)
		if(j->num<temp->num)
		temp=j;
		if(i!=temp)
		swap(i,temp);
	}
}
/*按姓名排序*/ 
void  SortbyName(STU *stu)
{
	STU *i,*j,*temp;
	for(i=stu;i->next!=NULL;i=i->next)
	{
		temp=i;
		for(j=i->next;j!=NULL;j=j->next)
			if(strcmp(j->name,i->name)<0)
				temp=j;
		if(temp!=i)
		swap(i,temp);
	}
}
/*按学号查找*/ 
void  SearchbyNum(STU *stu, int m)
{
	long number;
	STU *i;
	int j;
	printf("INput the number you want to search:");
	scanf("%ld",&number);
	for(i=stu;i!=NULL;i=i->next)
	{
		if(i->num==number)
		{
			printf("%ld\t%s\t",i->num,i->name);
			for(j=0;j<m;j++)
			{
				printf("%0.f\t",i->score[j]);
			}
			printf("%0.f\t%0.f\n",i->sum,i->aver);
			return;
		}
	}
	printf("Not found!\n");
}
/*按姓名查找*/ 
void  SearchbyName(STU *stu, int m)
{
	char x[MAX_LEN];
	int j;
	STU *i=stu;
	printf("Input the name you want to search:\n");
	scanf("%s",x);
	for( ;i!=NULL;i=i->next)
	{
		if(strcmp(stu->name,x)==0)
		{
			printf("%ld\t%s\t",stu->num,stu->name);
			for(j=0;j<m;j++)
			{
				printf("%0.f\t",stu->score[j]);
			}
			printf("%0.f\t%0.f\t",stu->sum,stu->aver);
			return;
		}
	}
	printf("Not found!\n");
}
/*数据分析*/ 
void  StatisticAnalysis(STU *stu,int m)
{
	int j,total,k,t[6];
	STU *i;
	for(j=0;j<m;j++)
	{
		printf("For course %d:\n",j+1);
		memset(t,0,sizeof(t));
		for(i=stu;i!=NULL;i=i->next)
		{
			if(i->score[j]>=0&&i->score[j]<=60) t[0]++;
			else if(i->score[j]<70) t[1]++;
			else if(i->score[j]<80) t[2]++;
			else if(i->score[j]<90) t[3]++;
			else if(i->score[j]<100) t[4]++;
			else if(i->score[j]==100) t[5]++;
		}
		for(total=0,k=0;k<6;k++)
		{
			total+=t[k];
		}
		for(k=0;k<=5;k++)
		{
			if(k==0)
			printf("<60\t%d\t%.2f%%\n",t[0],t[0]*1.0/total*100);
			else if(k==5)
			printf("%d\t%d\t%.2f%%\n",100,t[4],t[4]*1.0/total*100);
			else 
			printf("%d-%d\t%d\t%.2f%%\n",50+k*10,60+k*10,t[k],t[k]*1.0/total*100);
		}
	}
}
/*打印函数*/ 
void PrintScore(STU *stu,int m)
{
	int j;
	STU *i;
	for(i=stu;i!=NULL;i=i->next)
	{
		printf("%ld\t%s\t",i->num,i->name);
		for(j=0;j<m;j++)
		{
			printf("%.0f\t",i->score[j]);
		}
		printf("%.0f\t%.0f\n",i->sum,i->aver);
	}
 } 
 /*从文件中输入*/ 
void  ReadfromFile(STU *stu,int *n,int *m)
{
	FILE *fp;
	int i,j;
	int temp = *n;
	if((fp = fopen("student.txt", "r")) == NULL)
	{ 	
		printf(" Fail to open student.txt ");
		return ;
	}
	else
	{

		fscanf(fp, "%d\t%d\n",n, m);
		if(temp<*n)
		{
			free(stu);
			distribute(&stu,*n);
		}

		for(i=0;i<*n;i++)
		{
			fscanf(fp,"%12ld%12s", &stu->num, stu->name);
			for(j=0;j<*m;j++)
			{
				fscanf(fp,"%12.0f", &stu->score[j]);
			}
			fscanf(fp, "%12.0f%12.0f\n", &stu->sum, &stu->aver);
			stu=stu->next;
		}
		printf("Import Successfully!\n");
	}
}
/*输出到文件*/ 
void  WritetoFile(STU *stu,int n,int m)
{
	FILE  *fp;
	int i,j;
	if((fp = fopen("student.txt", "w"))==NULL)
	{
		printf("Fail to open student.txt ");
		return;
	}
	else
	{
		fprintf(fp, "%d\t%d\n", n, m);
		for(i=0;i<n;i++)
		{
			fprintf(fp, "%12ld%12s", stu->num, stu->name);
			for(j=0;j<m;j++) 	
			{
				fprintf(fp,"%12.0f", stu->score[j]);
			}
			fprintf(fp,"%12.0f%12.0f\n", stu->sum, stu->aver );
			stu=stu->next;
		}
		printf("Export Successfully!\n");
	}
	fclose(fp);
}
/*删除学生信息*/
STU *Delete(STU *head)  
{  
	long num;
	char a[5],name[10],c;
    STU *node1=head;  
    STU *node2=NULL;  
    scanf("%c",&c);
    while(c!='\n')
    {
    	scanf("%c",&c);
	}
    printf("Do you want to enter name or num\n");
    gets(a);
    if(strcmp(a,"name")==0)
    {
    	printf("Please enter the name of the student you want to delete.\n");
    	gets(name);
    	if (head==NULL)  
    {  
        return NULL;  
    }   
    else  
    {  
        if (strcmp(node1->name,name)==0)  
        {  
            head=head->next;  
            free(node1);  
            return head;  
        }   
        else  
        {  
            while (node1!=NULL)  
            {  
                node2=node1;  
                node2=node2->next;  
                if (strcmp(node2->name,name)==0)  
                {  
                    node1->next=node2->next;  
                    free(node2);  
                    break;  
                }  
                node1=node1->next;  
            }  
            return head;  
        }  
    }  
    	
	}
    else if(strcmp(a,"num")==0)
    {
    printf("Please enter the num of the student you want to delete.");
    scanf("%ld",&num);
    if (head==NULL)  
    {  
        return NULL;  
    }   
    else  
    {  
        if (node1->num==num)  
        {  
            head=head->next;  
            free(node1);  
            return head;  
        }   
        else  
        {  
            while (node1!=NULL)  
            {  
                node2=node1;  
                node2=node2->next;  
                if (node2->num==num)  
                {  
                    node1->next=node2->next;  
                    free(node2);  
                    break;  
                }  
                node1=node1->next;  
            }  
            return head;  
        }  
    }  
	}
}  
/*根据总成绩进行区间查找*/ 
void  SearchInaInterval(STU *stu,int m)
{
	STU *head=stu;
	int lower=0,upper=-1,j,i=0;
	SortbyScore(stu,Descending);
	for( ;head!=NULL;head=head->next)
	{
		head->sum=0;
		for(j=0;j<m;j++)
		{
			head->sum+=head->score[j];
		}
		stu->aver=m>0?stu->sum/m:-1;
	}
	while(upper<lower)
	{
	printf("Please enter the Interval upper limit and Interval lower limit(sum score)\n");
	scanf("%d%d",&upper,&lower);
}
	for( ;stu!=NULL;stu=stu->next)
	{
		if(stu->sum<=upper&&stu->sum>=lower)
		{
		i++;
		printf("%10ld%10s\t", stu->num, stu->name);
		for(j=0;j<m;j++)
		printf("%.0f\t", stu->score[j]);
		printf("%.0f\t%.0f\n", stu->sum, stu->aver);
		}
	}
	if(i==0)
	printf("Not Found\n");
	else
	printf("%d students' score are between %d and %d",i,lower,upper);
}
/*用于计算学分绩*/
void CreditGrade(STU *stu,int m)
{
	int i,count=1,countc=0;/*countc用于记录考试课门数*/ 
	float sumcredit=0;
	STU *pi,*j,*k,*b;
	pi=j=b=stu;
	char a[MAX_LEN],c;
	CLASS cla[COURSE_NUM];
	for(i=0;i<m;i++)
	{
		strcpy(a,"a");
		while(!(strcmp(a,"y")==0||strcmp(a,"Y")==0||strcmp(a,"n")==0||strcmp(a,"N")==0))
		{
		printf("Is the %d course a compulsory course?(input 'y'or'n')",i+1);
		scanf(" %s",a);
		scanf("%c",&c);
		while(c!='\n')
    	{
    	scanf("%c",&c);
		}
     	}
		if(strcmp(a,"y")==0||strcmp(a,"Y")==0)
		{
		countc++; 
		printf("Please input the credit");
		scanf("%d",&cla[i].point);
		sumcredit+=cla[i].point;
		}
		else
		cla[i].point=0;
	}
	for( ;stu!=NULL;stu=stu->next)
	{
		stu->creditgrade=0;
		for(i=0;i<m;i++)
		{
			stu->creditgrade+=cla[i].point*stu->score[i];
		}
		stu->creditgrade/=sumcredit;
	}
	for( ;pi!=NULL;pi=pi->next)
	{
		k=pi;
		for(j=pi->next;j!=NULL;j=j->next)
		if(j->creditgrade>pi->creditgrade)
		k=j;
		if(k!=pi)
		swap(pi,k);
	}
	if(countc!=0)
	for( ;b!=NULL;b=b->next)
	{
	printf("num=%ld name=%s creditgrade=%.2f rank=%d\n",b->num,b->name,b->creditgrade,count);
	count++;
	}
	else if(countc==0)
	printf("There is no compulsory course\n");
}