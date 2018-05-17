#pragma once

#include "Functions.h"

#define NUL -2

#define COIN 1		//tien, an dc +2d
#define TYPE_1 2	//dan, an dc +20 dan
#define TYPE_2 3	//hoa vat can thanh tien

#define MAX_ITEM 3

#define ITEM_RATE 5
#define TYPE_1_2_RATE 20
#define TYPE_2_RATE 10

//RADIUS = 0

//Khoi tao item
void khoiTaoItem(Item &new_item, int type, int x = NUL, int y = NUL)
{
	if (x == NUL && y == NUL)
	{
		new_item.td.y = SMALLEST_Y;
		new_item.td.x = random(SMALLEST_X, BIGGEST_X);	// can dieu chinh de ko trung voi vat can
	}
	else {
		new_item.td.y = y;
		new_item.td.x = x;
	}
	new_item.type = type;
	switch (type)
	{
		case COIN:
			new_item.hd = '$';
			return;
		case TYPE_1:
			new_item.hd = '*';
			return;
		case TYPE_2:
			new_item.hd = '?';
			return;
	}
}

void convertBarrierToCoin(Barrier &barrier, std::list<Item> &list_item)
{
	Item new_item;
	
	int x_barrier = barrier.td.x;
	int y_barrier = barrier.td.y;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (isInMapY(y_barrier + i - 1) && barrier.hd_vc[i][j] != ' ')
			{
				khoiTaoItem(new_item, COIN, x_barrier + j - 1, y_barrier + i - 1);
				list_item.push_back(new_item);
			}
		}
	}
}

void convertAllBarrierToCoins(std::list<Barrier> &list_barrier, std::list<Item> &list_item)
{
	std::list<Barrier>::iterator cursor, end;
	for (cursor = list_barrier.begin(), end = list_barrier.end(); cursor != end; cursor++)
	{
		convertBarrierToCoin(*cursor, list_item);
	}
	list_barrier.clear();
}

void itemActive(Item &item, unsigned int &diem, int &dan, std::list<Barrier> &list_barrier, std::list<Item> &list_item)
{
	switch (item.type)
	{
	case COIN:			// an tien + diem
		diem += 2;
		return;
	case TYPE_1:		// an dan duoc + 20 dan
		dan += 20;
		return;
	case TYPE_2:		// hoa tat ca cac vat can thanh tien
		convertAllBarrierToCoins(list_barrier, list_item);
		return;
	}
}


//Kiem tra xem item co xuat hien khong
//Neu ko xuat hien tra ve NUL
//Neu xuat hien tra ve item type;
int dieuKienSinhItem(std::list<Item> &list_item)
{
	//20% ra item
	bool h = chance(ITEM_RATE); 

	if (list_item.size() < MAX_ITEM && h) {
		h = chance(TYPE_1_2_RATE);
		//ra coin
		if (!h)
		{
			return COIN;
		}
		else {
			h = chance(TYPE_2_RATE);
			return h ? TYPE_2 : TYPE_1;
		}
	}
	return NUL;	
}

//Kiem tra va cham giua item va vat can
bool itemVaChamCar(Item &item, Car &car)
{
	int x1 = item.td.x,
		y1 = item.td.y,

		x2 = car.td.x,
		y2 = car.td.y;

	return (abs(x2 - x1) < 2 && abs(y2 - y1) < 2);
}


//Ham update vi tri cho item
//Tra ve false khi item ra ngoai man hinh => remove
bool updateItem(Item &item)
{
	if (!isInMapY(item.td.y + 1))	//ra khoi mna hinh
		return false;

	item.td.y++;			//di chuyen xuong
	return true;
}

//Ham sinh ra item (tren man hinh)
void itemGenerator(std::list<Item> &list_item)
{
	int isGenerate = dieuKienSinhItem(list_item);
	if (isGenerate != NUL) {
		Item new_item;
		khoiTaoItem(new_item, isGenerate);
		list_item.push_back(new_item);	//them vao list
	}
}

//Ham update trang thai cua nhung vien item co tren man hinh
//Cho item di chuyen len va kiem tra va cham voi vat can
bool updateItems(std::list<Item> &list_item, Car &car, unsigned int &diem, int &dan, std::list<Barrier> &list_barrier)
{
	std::list<Item>::iterator cursor, end;

	itemGenerator(list_item);

	for (cursor = list_item.begin(), end = list_item.end(); cursor != end;)
	{
		//di chuyen item, tra ve false khi item ra khoi ngoai man hinh => remove item
		bool check_vitri = updateItem(*cursor);

		//check va cham voi xe
		bool check_vacham = itemVaChamCar(*cursor, car);

		// neu ra ngoai man hinh || va cham xe
		if (!check_vitri || check_vacham) {
			if (check_vacham)
				itemActive(*cursor, diem, dan, list_barrier, list_item);
			cursor = list_item.erase(cursor);	//remove ra khoi list
		}
		else {
			++cursor;	//tranh loi khi su dung erase
		}

	}

	return true;
}

//Ve vien item len buffer
void drawItemOnBuffer(Item &item, Cell map[CHIEU_DAI][CHIEU_RONG], int color)
{
	//tách hàm để dễ quản lí.
	int x = item.td.x;
	int y = item.td.y;
	map[y][x].character = item.hd;
	map[y][x].color = color;
}

//Ve TAT CA vien item len buffer
void drawItemsOnBuffer(std::list<Item> &list_item, Cell map[CHIEU_DAI][CHIEU_RONG], int color)
{
	std::list <Item>::iterator cursor, end;
	//in vat can len map.
	for (cursor = list_item.begin(), end = list_item.end(); cursor != end; ++cursor)
	{
		drawItemOnBuffer(*cursor, map, color);
	}
}

