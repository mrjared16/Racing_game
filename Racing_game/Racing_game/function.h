#pragma once
#include <stdio.h>
#include <iostream>
#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include<list>
#include<mmsystem.h>
#include<string.h>
#include <windows.h>
void gotoXY(int column, int line);
void ShowConsoleCursor(bool showFlag);
int random(int start, int end);
using namespace std;



HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
int index = 1;
//12 = red, 15 = white-----> this.colorit(12); this.colorit(15);
void colorit(int col)
{
	SetConsoleTextAttribute(hstdout, col);
}

#define CHIEU_RONG 30
#define CHIEU_DAI 25
struct ACell
{
	unsigned char character;
	unsigned int color;
};
struct ToaDo
{
	int x, y;
};
struct Xe
{
	ToaDo td;
	char hd_xe[3][3];
};

struct VatCan
{
	ToaDo td;
	char hd_vc[3][3];
};
struct Tien//lưu cả tiền và vật phẩm cho tiện.
{
	ToaDo td;
	char a;
};
struct Record
{
	char name[26];
	int score;
};
struct Dan
{
	ToaDo td;
};