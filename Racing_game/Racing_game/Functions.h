#pragma once
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <list>
#include <string>
#include "Console.h"
#include <iostream>
using namespace std;

extern void huongdan();
extern void scoreMenu();
extern void play(bool auto_play = false);

#define CHIEU_RONG 30
#define CHIEU_DAI 25

#define SMALLEST_X 1
#define BIGGEST_X (CHIEU_RONG - 2)

#define SMALLEST_Y 0
#define BIGGEST_Y (CHIEU_DAI - 1)

#define RED 4
#define YELLOW 6
#define WHITE 15
#define LIGHT_RED 12
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_YELLOW 14

#define MAX_PLAYER_NAME 26

struct Cell
{
	unsigned char character;
	unsigned int color;
};

struct ToaDo
{
	int x, y;
};

//Xe
struct Car
{
	ToaDo td;
	char hd_xe[3][3];
};

//Vat can
struct Obstacle
{
	ToaDo td;
	int state = 0;	
	//0: bt
	//1: bi dan ban trung
	// co the tuy bien bien thanh hinh dang bat ky qua ham set hinh dang
	char hd_vc[3][3];
};

struct Item
{
	ToaDo td;
	int type;
	//1: coin
	//2: item_1: dan: 20 vien
	//3: item_2: dang phat trien
	char hd;
	//$, *, ?
};

//Dan
struct Bullet
{
	ToaDo td;
	char hd = 248;	//giong chu 'o'
};

struct Record
{
	//char name[] = {0};
	char name[MAX_PLAYER_NAME] = {};
	int score;
};

struct Level {
	int diem;			
	int level;			
	int sleep_time;				//thoi gian nghi de ve lai man hinh, cang nho thi ve lai cang nhieu => toc do game tang
	int max_obstacle;			//so vat can toi da
	int rate_generate_obstacle;	//ti le sinh vat can
	int max_amplitude;			//bien do dao dong toi da
	int rate_fluctuation;		//ti le dao dong
};

void mainMenu();
//extern void huongdan();

//Lay ngau nhien mot gia tri trong doan [start, end]
int random(int start, int end)
{
	return start + rand() % (end + 1 - start);
}

//Ham nhu mot phep quay thu, neu may man dat dc ti le phan tram thi tra ve true
//Dung de sinh dan, item, ...
bool chance(int percent)
{
	int ran = random(1, 100);
	return (ran <= percent);
}

//Kiem tra toa do x nam ngang co nam trong map ko
bool isInMapX(int x)
{
	return (x >= SMALLEST_X && x <= BIGGEST_X); // chieu rong da tinh luon 2 bien
}

//Kiem tra toa do y nam thang dung co nam trong map ko
bool isInMapY(int y)
{
	return (y >= SMALLEST_Y && y <= BIGGEST_Y);
}

//Kiem tra toa do (x,y) co thuoc map khong
bool isInMap(int x, int y)
{
	return isInMapX(x) && isInMapY(y);
}

//Hien thi mot nut "back" tra hinh, hien thi back va cho nguoi dung an phim enter de thuc hien tiep
void showBackButton(int x = -1, int y = -1) {
	if (x != -1 && y != -1)
		gotoXY(x, y);
	setColor(LIGHT_RED);
	printf("Back.");
	while (_getch() != 13);
}

//Hien thi cac thong so co ban khi choi game
//Level, Diem, Dan
void showStats(const char *content[], int stat[], int n, int x_start, int y_start)
{
	for (int i = 0; i < n; i++)
	{
		gotoXY(x_start, y_start + i);
		printf(content[i], stat[i]);
	}
}

//Hieu ung dong cho cac menu
void MenuFuntions(const char *label[], int len, int &index, int selected_color, int x_start, int y_start)
{
	int key = 0;

	setColor(WHITE);
	while (_kbhit()) _getch();	//clear input buffer: loi khi di chuyen theo chieu doc, menu pause xay ra loi

	while (key != 13)
	{
		for (int i = 0; i < len; i++)
		{
			gotoXY(x_start, y_start + i);
			
			if (index != i + 1) {	//unselected
				printf(label[i]);
				continue;
			}

			setColor(selected_color);
			printf(label[i]);
			setColor(WHITE);
		}
		key = _getch();
		if (key == 80)
		{
			index++;
		}
		if (key == 72)
		{
			index--;
		}
		if (index == len + 1)
		{
			index = 1;
		}
		if (index == 0)
		{
			index = len;
		}
	}
}

//An menu
void hideMenu(int len, int x_start, int y_start)
{
	for (int i = 0; i < len; i++)
	{
		gotoXY(x_start, y_start + i);
		printf("                        ");
	}
}


void mainMenu()
{
	system("cls");		//xóa màn hình, ví dụ người dùng từ mục điểm cao trở ra, pbải xóa màn hình của giao diện điểm cao.
						//nếu người dùng không trở ra từ ""Tiếp tục'" thì không có dòng Nhan 9 de tiep tuc.			
	gotoXY(8, 0);
	setColor(LIGHT_CYAN);
	printf("RACING GAME");

	int index = 1;
	int n_label = 5;
	const char *label[] = { "New game.", "Hall of Fame.", "CPU vs CPU.", "Help.", "Exit." };

	MenuFuntions(label, n_label, index, LIGHT_RED, 8, 2);

	//điều kiện chạy thuật toán.
	switch (index) {
		case 1:
			play();
			return;
		case 2:
			scoreMenu();
			return;
		case 3:
			play(true);
			return;
		case 5:
			exit(0);
		case 4:
			huongdan();
			showBackButton(32, 9);
			mainMenu();		//ép buộc người dùng nhấn Enter để trở về menu chính.
			return;
	}
}

/*void oldmainMenu()
{
	system("cls");		//xóa màn hình, ví dụ người dùng từ mục điểm cao trở ra, pbải xóa màn hình của giao diện điểm cao.
						//nếu người dùng không trở ra từ ""Tiếp tục'" thì không có dòng Nhan 9 de tiep tuc.
	int key = 0;
	int index = 1;
	while (key != 13)
	{
		//system("cls");
		gotoXY(8, 0);
		setColor(15);
		printf("RACING GAME");

		setColor(15);		//Màu trắng
		if (index == 1)
		{
			setColor(12);		//Nếu được chon sẽ chuyển thành màu đỏ
		}
		gotoXY(8, 2);
		printf("New game.\n");

		setColor(15);
		if (index == 2)
		{
			setColor(12);
		}
		gotoXY(8, 3);
		printf("High scores.\n");

		setColor(15);
		if (index == 3)
		{
			setColor(12);
		}
		gotoXY(8, 4);
		printf("CPU vs CPU.\n");

		setColor(15);
		if (index == 4)
		{
			setColor(12);
		}
		gotoXY(8, 5);
		printf("Help.\n");

		setColor(15);
		if (index == 5)
		{
			setColor(12);
		}
		gotoXY(8, 6);
		printf("Exit.\n");

		key = _getch();
		if (key == 80)
		{
			++index;
		}
		else if (key == 72)
		{
			--index;
		}
		if (index == 6)
		{
			index = 1;
		}
		if (index == 0)
		{
			index = 5;
		}
	}

	//điều kiện chạy thuật toán.
	if (index == 1) play();
	if (index == 2) scoreMenu();
	if (index == 4) { 
		huongdan(); 

		gotoXY(16, 7);
		setColor(12);
		printf("Back.");
		while (_getch() != 13);
		mainMenu();		//ép buộc người dùng nhấn Enter để trở về menu chính.
	}

	// con lai se thoat
	//if (index == 5 || index == 0)  return;
}*/