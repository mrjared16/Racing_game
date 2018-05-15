#pragma once

#include "Functions.h"

#define MAX_COIN 2

//Khoi tao coin
void khoiTaoCoin(Coin &new_coin)
{
	new_coin.td.y = -3;
	new_coin.td.x = random(2, CHIEU_RONG - 3);
}

//Dieu kien de sau nay su dung
bool dieuKienSinhCoin(std::list<Coin> &list_coin)
{
	int i = random(0, 20);
	if (list_coin.size() < MAX_COIN && i == 1) {
		return true;
	}
	return false;	
}

//Kiem tra va cham giua coin va vat can
bool coinVaChamCar(Coin &coin, Car &car)
{
	int x1 = coin.td.x,
		y1 = coin.td.y,

		x2 = car.td.x,
		y2 = car.td.y;

	return (abs(x2 - x1) < 3 && abs(y2 - y1) < 3);
}


//Ham update vi tri cho coin
//Tra ve false khi coin ra ngoai man hinh => remove
bool updateCoin(Coin &coin)
{
	if (coin.td.y > CHIEU_DAI)	//ra khoi mna hinh
		return false;

	coin.td.y++;			//di chuyen len
	return true;
}

//Ham sinh ra coin (tren man hinh)
void coinGenerator(std::list<Coin> &list_coin)
{
	//neu coin van con ma list chua co coin || du khoang cach ra vien coin tiep theo
	if (dieuKienSinhCoin(list_coin)) {
		Coin new_coin;
		khoiTaoCoin(new_coin);
		list_coin.push_back(new_coin);	//them vao list
	}
}

//Ham update trang thai cua nhung vien coin co tren man hinh
//Cho coin di chuyen len va kiem tra va cham voi vat can
bool updateCoins(std::list<Coin> &list_coin, Car &car, int &diem)
{
	std::list<Coin>::iterator cursor;

	coinGenerator(list_coin);

	for (cursor = list_coin.begin(); cursor != list_coin.end();)
	{
		bool check = coinVaChamCar(*cursor, car);
		//di chuyen coin, tra ve false khi coin ra khoi ngoai man hinh => remove coin
		if (!updateCoin(*cursor) || check) {
			if (check)
				diem += 2;
			cursor = list_coin.erase(cursor);
		}
		else {
			cursor++;	//tranh loi khi su dung erase
		}

	}

	return true;
}

//Ve vien coin len buffer
void drawCoinOnBuffer(Coin &coin, Cell map[CHIEU_DAI][CHIEU_RONG], int color)
{
	//tách hàm để dễ quản lí.
	int x = coin.td.x;
	int y = coin.td.y;
	map[y][x].character = coin.hd;
	map[y][x].color = color;
}

//Ve TAT CA vien coin len buffer
void drawCoinsOnBuffer(std::list<Coin> &list_coin, Cell map[CHIEU_DAI][CHIEU_RONG], int color)
{
	std::list <Coin>::iterator cursor;
	//in vat can len map.
	for (cursor = list_coin.begin(); cursor != list_coin.end(); cursor++)
	{
		drawCoinOnBuffer(*cursor, map, color);
	}
}

