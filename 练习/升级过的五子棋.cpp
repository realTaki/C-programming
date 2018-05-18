#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include<windows.h>
#define MAXXY 15 //棋盘大小
int p[MAXXY][MAXXY] = {0};//对局信息
short Cx, Cy, cx, cy;//当前光标位置和上一次光标位置
int now = 1,count = 0;//黑方先手，统计回合数
int victor;//记录胜利信息
HANDLE hOut;
COORD pos;

void print(void) {//打印棋盘
	int i;
	printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　\n"); 
	printf("　┏━┯━┯━┯━┯━┯━┯━┯━┯━┯━┯━┯━┯━┯━┓　\n");
	for (i = 3; i < 30; i++) 
	{
		if ((i % 2) == 1 && i != 31)
			printf("　┃　│　│　│　│　│　│　│　│　│　│　│　│　│　┃　\n");
		else printf("　┠—┼—┼—┼—┼—┼—┼—┼—┼—┼—┼—┼—┼—┼—┨　\n");
	}
	printf("　┗━┷━┷━┷━┷━┷━┷━┷━┷━┷━┷━┷━┷━┷━┛　\n");
	printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　\n");
}

void sign(void){//显示光标图案
	 pos = { 4 * (cx - 1),2 * (cy-1 ) }; SetConsoleCursorPosition(hOut, pos); printf("　");
	 pos = { 4 * cx ,2 * (cy - 1) }; SetConsoleCursorPosition(hOut, pos); printf("　");
	 pos = { 4 * (cx - 1),2 * cy }; SetConsoleCursorPosition(hOut, pos); printf("　");
	 pos = { 4 * cx ,2 * cy  }; SetConsoleCursorPosition(hOut, pos); printf("　");
	 if (Cx<1)Cx = MAXXY;//如果光标位置越界则移动到对侧
	 if (Cy<1)Cy = MAXXY;
	 if (Cx>MAXXY)Cx = 1;
	 if (Cy>MAXXY)Cy = 1;
	 pos = { 4 * (Cx - 1),2 * (Cy - 1) }; SetConsoleCursorPosition(hOut, pos); printf("┏");
	 pos = { 4 * Cx ,2 * (Cy - 1) }; SetConsoleCursorPosition(hOut, pos); printf("┓");
	 pos = { 4 * (Cx - 1),2 * Cy }; SetConsoleCursorPosition(hOut, pos); printf("┗");
	 pos = { 4 * Cx ,2 * Cy }; SetConsoleCursorPosition(hOut, pos); printf("┛");
}

int put(void) {//在当前光标位置走子，如果非空，则返回0表示失败
		if (p[Cx-1][Cy-1] == 0)
		{
			p[Cx-1][Cy-1] = now;//改变该位置数据
			pos = { (4 * Cx)-2,2 * Cy-1 };
			SetConsoleCursorPosition(hOut, pos);
			if(now==1)printf("●");else printf("○"); 
			count++;
			return 1;//返回1表示成功
		}
		else return 0;		
	}

int Check(void)//胜负检查，即判断当前走子位置有没有造成五连珠的情况
{
	int w = 1, x = 1, y = 1, z = 1, i;//累计横竖正斜反斜四个方向的连续相同棋子数目
	for (i = 1; i<5; i++)if (Cy + i<MAXXY&&p[Cx-1][Cy-1 + i] == now)w++; else break;//向下检查
	for (i = 1; i<5; i++)if (Cy - i>0 && p[Cx-1][Cy-1 - i] == now)w++; else break;//向上检查
	if (w >= 5)return now;//若果达到5个则判断当前走子玩家为赢家
	for (i = 1; i<5; i++)if (Cx + i<MAXXY&&p[Cx-1 + i][Cy-1] == now)x++; else break;//向右检查
	for (i = 1; i<5; i++)if (Cx - i>0 && p[Cx-1 - i][Cy] == now)x++; else break;//向左检查
	if (x >= 5)return now;//若果达到5个则判断当前走子玩家为赢家
	for (i = 1; i<5; i++)if (Cx + i<MAXXY&&Cy + i<MAXXY&&p[Cx -1+ i][Cy-1 + i] == now)y++; else break;//向右下检查
	for (i = 1; i<5; i++)if (Cx - i>0 && Cy - i>0 && p[Cx-1 - i][Cy-1 - i] == now)y++; else break;//向左上检查
	if (y >= 5)return now;//若果达到5个则判断当前走子玩家为赢家
	for (i = 1; i<5; i++)if (Cx + i<MAXXY&&Cy - i>0 && p[Cx-1 + i][Cy -1- i] == now)z++; else break;//向右上检查
	for (i = 1; i<5; i++)if (Cx - i>0 && Cy + i<MAXXY&&p[Cx-1 - i][Cy-1 + i] == now)z++; else break;//向左下检查
	if (z >= 5)return now;//若果达到5个则判断当前走子玩家为赢家
	return 0;//若没有检查到五连珠，则返回0表示还没有玩家达成胜利
}

void begin(void) {
	int i, j;
	for(i=0;i<MAXXY;i++)for(j=0;j<MAXXY;j++)p[i][j] =  0 ;
	Cx = Cy = cx = cy = 8;
	victor = 0; count = 0; now = 1;
	print();
	sign();
}

void RunGame(void) { //游戏开始
	begin();
	int input;
	while((input=getch())!= 27)
	{
		if (input == 0x20)//如果是空格则开始走子
		{
			if (put()) { victor = Check(); now = 3 - now; if (victor!=0)break; }
		}
		else if (input == 0xE0)//如果按下的是方向键，会填充两次输入，第一次为0xE0表示按下的是控制键
		{
			input = getch();//获得第二次输入信息
			cx = Cx; cy = Cy;
			switch (input)//判断方向键方向并移动光标位置
			{
			case 0x4B:
				Cx--;
				break;
			case 0x48:
				Cy--;
				break;
			case 0x4D:
				Cx++;
				break;
			case 0x50:
				Cy++;
				break;
			}
			sign();
		}		
	}
	if (input == 27)exit(0);
	pos = { 30,16 };
	if (victor == 1)printf("黑方胜利！按任意键继续");
	else if (victor == 2)printf("白方胜利！按任意键继续");
	else if (count == 15 * 15)printf("平局！按任意键继续");
	getch();
}

int main(void)//主函数
{
	system("title 黑川的五子棋");//设置标题,对比SetConsoleTitle("黑川的五子棋");
	system("mode con cols=63 lines=33");//设置窗口大小
	system("color 80");//设置颜色
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	while(1)RunGame();//循环执行游戏
}