#pragma once
#include "Functions.h"

#define MOVE_UP 2
#define MOVE_DOWN -2

#define MOVE_RIGHT 1
#define MOVE_LEFT -1

#define CAR_RADIUS 1

void setCarAppearance(Car &car)
{
	//o o 
	//:X:
	//o o
	//quy định các giá trị trong mảng 3*3
	car.hd_xe[0][0] = car.hd_xe[2][0] = car.hd_xe[0][2] = car.hd_xe[2][2] = 'o';
	car.hd_xe[0][1] = car.hd_xe[2][1] = ' ';
	car.hd_xe[1][0] = car.hd_xe[1][2] = ':';
	car.hd_xe[1][1] = 'X';
}

void khoiTaoCar(Car &car)
{
	car.td.x = BIGGEST_X / 2;
	car.td.y = BIGGEST_Y - CAR_RADIUS;
	setCarAppearance(car);
}

void moveCar(Car &car, int direction)
{
	switch (direction)
	{
	case MOVE_UP:
		if (isInMapY(car.td.y - CAR_RADIUS - 1))
			car.td.y--;
		return;
	case MOVE_DOWN:
		if (isInMapY(car.td.y + CAR_RADIUS + 1))
			car.td.y++;
		return;
	case MOVE_RIGHT:
		if (isInMapX(car.td.x + CAR_RADIUS + 1))
			car.td.x++;
		return;
	case MOVE_LEFT:
		if (isInMapX(car.td.x - CAR_RADIUS - 1))
			car.td.x--;
		return;
	}
}

void drawCarOnBuffer(Car &car, Cell map[CHIEU_DAI][CHIEU_RONG], int color)
{
	int x_xe = car.td.x;
	int y_xe = car.td.y;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			map[y_xe + i - 1][x_xe + j - 1].character = car.hd_xe[i][j];
			map[y_xe + i - 1][x_xe + j - 1].color = color;		//Màu trắng
		}
	}
}