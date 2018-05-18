#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#define N 21

int apple[3],num;
char score[3];
char tail[3]; 

void gotoxy(int x, int y)    //输出坐标 
{
        COORD pos;
        pos.X = x; 
        pos.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void color(int b)         //颜色函数 
{
    HANDLE hConsole = GetStdHandle((STD_OUTPUT_HANDLE)) ; 
    SetConsoleTextAttribute(hConsole,b) ;
} 

int Block(char head[2])   //判断出界 
{
        if ((head[0] < 1) || (head[0] > N) || (head[1] < 1) || (head[1] > N))
                return 1;
        return 0;
}

int Eat(char snake[2])   //吃了苹果 
{
        if ((snake[0] == apple[0]) && (snake[1] == apple[1]))
       {
                apple[0] = apple[1] = apple[2] = 0;
                gotoxy(N+44,10);
                color(13);
                printf("%d",score[0]*10);
                color(11);
                return 1;
           }
        return 0;
}

void Draw(char **snake, int len)    //蛇移动 
{
        if (apple[2]) 
		{
                gotoxy(apple[1] * 2, apple[0]);
                color(12);
                printf("●");
                color(11);
        }
        gotoxy(tail[1] * 2, tail[0]);
        if (tail[2]) 
         {  
		    color(num);
            printf("★");
            color(num);
         }
    else 
        printf("■");
        gotoxy(snake[0][1] * 2, snake[0][0]);
        color(num);
        printf("★");
        color(num);
        putchar('\n');
}

char** Move(char **snake, char dirx, int *len)   //控制方向 
{
        int i, full = Eat(snake[0]);
        memcpy(tail, snake[(*len)-1], 2);
        for (i = (*len) - 1; i > 0; --i) 
                memcpy(snake[i], snake[i-1], 2);
        switch (dirx) 
          { 
           case 'w': case 'W': --snake[0][0]; break;
              case 's': case 'S': ++snake[0][0]; break;
           case 'a': case 'A': --snake[0][1]; break;
           case 'd': case 'D': ++snake[0][1]; break;
           default: ;
         }  
        if (full)   
           { 
                snake = (char **)realloc(snake, sizeof(char *) * ((*len) + 1));
                snake[(*len)] = (char *)malloc(sizeof(char) * 2);
                memcpy(snake[(*len)], tail, 2);
                ++(*len);
                ++score[0];
                if(score[3] < 16) 
                ++score[3];
                tail[2] = 1;
           }
           else 
                tail[2] = 0;
                return snake;
}

void init(char plate[N+2][N+2], char ***snake_x, int *len)  //初始化 
{
        int i, j;
        char **snake = NULL;

        *len = 3;
        score[0] = score[3] =3;
        snake = (char **)realloc(snake, sizeof(char *) * (*len));
        for (i = 0; i < *len; ++i)
                snake[i] = (char *)malloc(sizeof(char) * 2);
                
        for (i = 0; i < 3; ++i) 
                {
                snake[i][0] = N/2 + 1;
                snake[i][1] = N/2 + 1 + i;
             } 
             
        for (i = 1; i <= N; ++i) 
                for (j = 1; j <= N; ++j) 
                        plate[i][j] = 1;
                         
        apple[0] = rand()%N + 1; apple[1] = rand()%N + 1;
        apple[2] = 1;

        for (i = 0; i < N + 2; ++i) 
                {
                gotoxy(0, i);
                for (j = 0; j < N + 2; ++j) 
                        {
                        switch (plate[i][j]) 
                                {
                             case 0: 
                                 color(12);printf("□");color(11); continue;
                        case 1: printf("■"); continue;
                             default: ;
                             }
                    }
                   putchar('\n');
            } 
        for (i = 0; i < (*len); ++i)
       {
                gotoxy(snake[i][1] * 2, snake[i][0]);
                printf("★");
            } 
        putchar('\n');
        *snake_x = snake;
}

void Manual()
{
        gotoxy(N+30,2);
        color(10);
        printf("按 W S A D 移动方向");
        gotoxy(N+30,4);
        printf("按 space 键暂停"); 
        gotoxy(N+30,8);
        color(11);
        printf("历史最高分为: ");
        color(12);
        gotoxy(N+44,8);
        printf("%d",score[1]*10);
        color(11);
        gotoxy(N+30,12);
        printf("你现在得分为: 0");         
}

int File_in()     //取记录的分数 
{
   FILE *fp;
   if((fp = fopen("C:\\tcs.txt","a+")) == NULL)
   {
            gotoxy(N+18, N+2);
     printf("文件不能打开\n");
         exit(0);
   }
   if((score[1] = fgetc(fp)) != EOF);
   else
   score[1] = 0;
   return 0;
}

int File_out()    //存数据 
{
        
        FILE *fp;
        if(score[1] > score[0]) 
        {gotoxy(10,10);
        color(12);
        puts("闯关失败 加油耶");
        gotoxy(0,N+2); 
        return 0;
        }
        if((fp = fopen("C:\\tcs.txt","w+")) == NULL)
        {
                printf("文件不能打开\n");
                exit(0);
        }
    if(fputc(--score[0],fp)==EOF)
           printf("输出失败\n");
    gotoxy(10,10);
        color(12);
        puts("恭喜您打破记录"); 
        gotoxy(0,N+2);
        return 0;
}

void Free(char **snake, int len)    //释放空间 
{
        int i;
        for (i = 0; i < len; ++i) 
                free(snake[i]);
        free(snake);
}

int main(void)
{
        int len;
        char ch = 'g';
        char a[N+2][N+2] = {{0}};
        char **snake;
        srand((unsigned)time(NULL));
        color(11);
        File_in();
        init(a, &snake, &len);
        Manual();
        while (ch != 0x1B)   // 按 ESC 结束 
         { 
                Draw(snake, len);
                if (!apple[2]) {
                        apple[0] = rand()%N + 1;
                        apple[1] = rand()%N + 1;
                        apple[2] = 1;
                        num++;
				        if(num>8)
					       num=0;
                }
                Sleep(200-score[3]*10);
                setbuf(stdin, NULL);
                if (kbhit())
                   {
                        gotoxy(0, N+2);
                        ch = getche();
                    }
                 snake = Move(snake, ch, &len); 
                 if (Block(snake[0])==1) 
                  {
                        gotoxy(N+2, N+2);
                        puts("你输了");
                        File_out();
                        Free(snake, len);
                        getche();
                        exit(0); 
                  }                        
        }
        Free(snake, len);
        exit(0);
}