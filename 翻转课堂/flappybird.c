#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>

#define DIS 22
#define BLAN 9 

typedef struct bird {
	COORD pos;
	int score;
}BIRD;

void Position(COORD pos) {
	HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Out, pos);
}

void CheakWall(COORD wall[]) {
	int i;
	COORD temp = { wall[2].X + DIS,rand() % 13 + 2 };

	if (wall[0].X < 10) {
		srand(time(0));
		wall[0] = wall[1];
		wall[1] = wall[2];
		wall[2] = temp;
	}

	for (i = 0; i < 3; i++) {
		temp.X = wall[i].X + 1;
		for (temp.Y = 1; temp.Y < wall[i].Y; temp.Y++) {
			Position(temp);
			printf("¡ö¡ö¡ö¡ö");
		}

		temp.X--;
		Position(temp);
		printf("¡ö¡ö¡ö¡ö¡ö");

		temp.Y += BLAN;
		Position(temp);
		printf("¡ö¡ö¡ö¡ö¡ö");

		temp.X++;
		for (; ++(temp.Y) < 27;) {
			Position(temp);
			printf("¡ö¡ö¡ö¡ö");
		}
	}
}

void PrtBird(BIRD *bird, int x) {
	Position(bird->pos);
	if (x)printf("§À¡ú");
	else printf("    ");
}

int CheakWin(COORD *wall, BIRD *bird) {
	if (bird->pos.X >= wall->X) {
		if (bird->pos.Y<wall->Y || bird->pos.Y>wall->Y + BLAN)return 0;
	}
	if (bird->pos.Y < 1 || bird->pos.Y>26)return 0;
	(bird->score)++;
	return 1;
}

void Begin(BIRD *bird) {
	COORD down = { 0,27 };
	COORD top = { 0,1 };
	system("cls");
	printf("¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T");
	Position(down);
	printf("¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T");
	Position(top);
	printf("%4d", bird->score);
}

int main(int argc, char* argv[]) {
	BIRD bird = { { 22,10 }, 0 };
	COORD wall[3] = { { 40,10 } ,{ 60,6 },{ 80,8 } };
	int i;

	while (CheakWin(wall, &bird)) {
		Begin(&bird);
		CheakWall(wall);
		PrtBird(&bird, 1);
		Sleep(200);
		PrtBird(&bird, 0);
		if (GetAsyncKeyState(VK_SPACE)) {
			bird.pos.Y -= 2;
		}
		else bird.pos.Y += 1;
		for (i = 0; i < 3; i++) {
			(wall[i].X)--;
		}
	}
	return 0;
}