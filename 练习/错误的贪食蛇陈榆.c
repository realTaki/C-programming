#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define H 8
#define L 16
char GameMap[H][L];//游戏地图
int key;//按键保存
int sum = 1, over = 0;//蛇的长度，游戏结束
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
struct Snake
{
	int x, y;//左边位置
	int now;//保存当前结点的方向，0，1，2，3分别代表左右上下
};
struct Snake Snake[H*L];
const char Shead = '@';//蛇头
const char Sbody = '#';//蛇身
const char Sfood = '*';//食物
const char Snode = '.';//‘。’在地图上显示为空
void Initial();//地图的初始化
void Create_Food();//在地图上随机产生食物
void Show();//刷新显示地图
void Button();//取出按键，并判断方向
void Move();//蛇的移动
void Check_Border();//检查舌头是否越界
void Check_Head(int x, int y);//检查蛇头移动后位置的情况

int main()
{
	Initial();
	Show();
	return 0;
}

void Initial()//地图的初始化
{
	int i, j;
	int hx, hy;
	system("title 贪吃蛇");//控制台的标题
	memset(GameMap, '.', sizeof(GameMap));//初始化地图全部为空
	system("cls");
	srand(time(0));//随机种子
	hx = rand() % H;
	hy = rand() % L;
	GameMap[hx][hy] = Shead;
	Snake[0].x = hx;
	Snake[0].y = hy;
	Snake[0].now = -1;
	Create_Food();//随机产生食物
	for (i = 0; i < H; i++)
	{
		for (j = 0; j < L; j++)
		{
			printf("%c", GameMap[i][j]);
		}
		printf("\n");
	}
	printf("按任意方向键开始游戏");
	getch();
	Button();
}

void Create_Food()//在地图上随机产生食物
{
	int fx, fy;
	while (1)
	{
		fx = rand() % H;
		fy = rand() % L;
		if (GameMap[fx][fy] == '.')//不能出现在蛇头的位置
		{
			GameMap[fx][fy] = Sfood;
			break;
		}
	}
}

void Show()//刷新显示地图
{
	int i, j;
	while (1)
	{
		Sleep(500);//延迟半秒，每半秒刷新一次地图
		Button();//判断按键
		Move();//开始动！
		if (over)
		{
			printf("\n**游戏结束**\n");
			getchar();
			break;
		}
		system("cls");//清空地图再显示刷新后的地图
		for (i = 0; i < H; i++)
		{
			for (j = 0; j < L; j++)
			{

				printf("%c", GameMap[i][j]);
			}
			printf("\n");
		}
		printf("按任意方向键开始游戏");
	}
}

void Button()
{
	if (kbhit() != 0)//检查当前是否有键盘输入，若有则返回一个非零值
	{
		while (kbhit() != 0)
			key = getch();//将按键从控制台中取出并保存到kry中
		switch (key)
		{
		case 97:
		case 65:
			Snake[0].now = 0;
			break;
		case 100:
		case 68:
			Snake[0].now = 1;
			break;
		case 119:
		case 87:
			Snake[0].now = 2;
			break;
		case 115:
		case 83:
			Snake[0].now = 3;
			break;
		}
	}
}

void Move()
{
	int i, x, y;
	int t = sum;//保存蛇的长度
				//记录当前蛇头的位置，并设置为空，蛇头先移动
	x = Snake[0].x;
	y = Snake[0].y;
	GameMap[x][y] = '.';
	Snake[0].x = Snake[0].x + dx[Snake[0].now];
	Snake[0].y = Snake[0].y + dy[Snake[0].now];
	Check_Border();
	Check_Head(x, y);
	if (sum == t)
	{
		for (i = 0; i < sum; i++)
		{
			if (i == 1)
				GameMap[Snake[i].x][Snake[i].y] = '.';
			if (i == sum - 1)
			{
				Snake[i].x = x;
				Snake[i].y = y;
				Snake[i].now = Snake[0].now;
			}
			else
			{
				Snake[i].x = Snake[i + 1].x;
				Snake[i].y = Snake[i + 1].y;
				Snake[i].now = Snake[i + 1].now;
			}
			GameMap[Snake[i].x][Snake[i].y] = '#';//移动后要置为‘#’的蛇身
		}
	}

}

void Check_Border()
{
	if (Snake[0].x < 0 || Snake[0].x >= H || Snake[0].y < 0 || Snake[0].y >= L)
		over = 1;
}

void Check_Head(int x, int y)
{
	if (GameMap[Snake[0].x][Snake[0].y] == '.')
	{
		GameMap[Snake[0].x][Snake[0].y] = '@';
	}
	else if (GameMap[Snake[0].x][Snake[0].y] == '*')
	{
		GameMap[Snake[0].x][Snake[0].y] = '@';
		Snake[sum].x = x;
		Snake[sum].y = y;
		Snake[sum].now = Snake[0].now;
		GameMap[Snake[sum].x][Snake[sum].y] = '#';
		sum++;
		Create_Food();
	}
	else
		over = 1;
}
