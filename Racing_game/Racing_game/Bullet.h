#pragma once

#include "Functions.h"

#define DISTANCE_BETWEEN_2_BULLETS 6

//RADIUS = 0

//Khoi tao bullet
void khoiTaoBullet(Bullet &new_bullet, Car &car)
{
	new_bullet.td.x = car.td.x;
	new_bullet.td.y = car.td.y - CAR_RADIUS;
}

/*//Dieu kien de sau nay su dung
bool dieuKienSinhBullet(int diem)
{
	//co the la an item hoac la duoc so diem cu the
	return (diem % 10 == 5);	//tam thoi de test
}*/

//Kiem tra va cham giua dan va vat can
bool bulletVaChamBarrier(Bullet &dan, Barrier &barrier)
{
	int x1 = dan.td.x,
		y1 = dan.td.y,

		x2 = barrier.td.x,
		y2 = barrier.td.y;

	return (abs(x2 - x1) < 2 && abs(y2 - y1) < 2 && y2 > -2);
}

//Kiem tra xem vien dan co trung vat can nao khong
bool checkVaChamBullet(Bullet &dan, std::list<Barrier> &list_barrier)
{

	std::list<Barrier>::iterator cursor;
	for (cursor = list_barrier.begin(); cursor != list_barrier.end(); cursor++)	
	{
		if (bulletVaChamBarrier(dan, *cursor)) {
			// do something
			(*cursor).state = GOT_SHOT;		//chuyen state thanh bi ban
			setBarrierAppearance(*cursor);	//set lai hinh dang cua vat can
			return true;
		}
	}

	return false;
}

//Ham update vi tri cho dan
//Tra ve false khi dan ra ngoai man hinh => remove
bool updateBullet(Bullet &bullet)
{
	if (!isInMapY(bullet.td.y - 1))	//ra khoi mna hinh
		return false;

	bullet.td.y--;			//di chuyen len
	return true;
}

//Ham sinh ra dan (tren man hinh)
void bulletGenerator(std::list<Bullet> &list_dan, Car &car, int &dan)
{
	//neu dan van con ma list chua co dan || du khoang cach ra vien dan tiep theo
	if (dan > 0 && (list_dan.empty() || car.td.y - list_dan.back().td.y >= DISTANCE_BETWEEN_2_BULLETS))
	{
		Bullet new_dan;
		khoiTaoBullet(new_dan, car);
		list_dan.push_back(new_dan);	//them vao list
		dan--;	// giam so dan
	}
}

//Ham update trang thai cua nhung vien dan co tren man hinh
//Cho dan di chuyen len va kiem tra va cham voi vat can
bool updateBullets(std::list<Bullet> &list_dan, std::list<Barrier> &list_barrier, Car &car, int &dan)
{
	std::list<Bullet>::iterator cursor;
	
	bulletGenerator(list_dan, car, dan);
	
	for (cursor = list_dan.begin(); cursor != list_dan.end();)
		{
		//di chuyen dan, tra ve false khi dan ra khoi ngoai man hinh => remove dan
		//kiem tra vat can co cham vat can khong, tra ve true khi va cham & doi hinh dang vat can
		if (!updateBullet(*cursor) || checkVaChamBullet(*cursor, list_barrier)) {
			cursor = list_dan.erase(cursor);
		}
		else {
			cursor++;	//tranh loi khi su dung erase
		}
		
	}
	
	return true;
}

//Ve vien dan len buffer
void drawBulletOnBuffer(Bullet &dan, Cell map[CHIEU_DAI][CHIEU_RONG], int color)
{
	//tách hàm để dễ quản lí.
	int x = dan.td.x;
	int y = dan.td.y;
	map[y][x].character = dan.hd;
	map[y][x].color = color;
}

//Ve TAT CA vien dan len buffer
void drawBulletsOnBuffer(std::list<Bullet> &list_dan, Cell map[CHIEU_DAI][CHIEU_RONG], int color)
{
	std::list <Bullet>::iterator cursor;
	//in vat can len map.
	for (cursor = list_dan.begin(); cursor != list_dan.end(); cursor++)
	{
		drawBulletOnBuffer(*cursor, map, color);
	}
}

