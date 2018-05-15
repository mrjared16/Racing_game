#pragma once
#include "Functions.h"

int khoangcach(Car &car, Barrier &barrier)
{
	return(sqrt(pow(abs(car.td.x - barrier.td.x), 2) + pow(abs(car.td.y - barrier.td.y), 2)));//tính khoảng cách giữa xe và vật cản
}

int sovctrongvungantoan(Car &car, std::list<Barrier> &list_vc)
{//tim số vật cản xe có thể bị đụng trúng
	int i = 0;
	for (std::list <Barrier>::iterator vc1 = list_vc.begin(); vc1 != list_vc.end(); vc1++)
	{
		if (abs(car.td.x - (*vc1).td.x) < 6 && ((*vc1).td.y < car.td.y) && abs((*vc1).td.y - car.td.y) < 10)
			i++;
	}
	return i;
}

int vcgannhat(Car &car, Barrier *p, std::list<Barrier> &list_vc)
{//tìm vật cản gần nhất để ưu tiên né
	int gannhat = 0;
	int kcngannhat = 1000;
	for (int i = 0, n = sovctrongvungantoan(car, list_vc); i < n; i++)
	{
		if (khoangcach(car, p[i]) < kcngannhat)
		{
			kcngannhat = khoangcach(car, p[i]);
			gannhat = i;
		}
	}
	return gannhat;
}
void tunhanphim(Car &car, std::list<Barrier> &list_vc)
{
	std::list <Barrier>::iterator cursor;
	if (sovctrongvungantoan(car, list_vc) == 1)//nếu chỉ có 1 vật cản thì né dễ hơn
	{
		Barrier *p = (Barrier *)malloc(sovctrongvungantoan(car, list_vc) * sizeof(Barrier));
		int i = 0;
		for (cursor = list_vc.begin(); cursor != list_vc.end(); cursor++)
		{
			if (abs(car.td.x - (*cursor).td.x) < 6 && ((*cursor).td.y < car.td.y) && abs((*cursor).td.y - car.td.y) < 10)
				p[i] = *cursor;
		}
		while (abs(p[0].td.x - car.td.x)<3 && (p[0].td.y <= car.td.y) && abs(p[0].td.y - car.td.y) < 6)
		{
			if (car.td.x > p[0].td.x)
			{
				car.td.x++;
			}
			if (car.td.x < p[0].td.x)
			{
				car.td.x--;
			}
			if (car.td.x == p[0].td.x)
			{
				int i = random(1, 2);
				if (i == 1)
					car.td.x--;
				else
					car.td.x++;
			}

		}

	}
	if (sovctrongvungantoan(car, list_vc) > 1)// khi có hơn 1 vật cản
	{
		Barrier *p = (Barrier *)malloc(sovctrongvungantoan(car, list_vc) * sizeof(Barrier));
		int i = 0;
		for (cursor = list_vc.begin(); cursor != list_vc.end(); cursor++)
		{
			if (abs(car.td.x - (*cursor).td.x) < 6 && ((*cursor).td.y < car.td.y) && abs((*cursor).td.y - car.td.y) < 10)
				p[i] = *cursor;
		}
		int trai = 0, phai = 0;
		for (int i = 0, n = sovctrongvungantoan(car, list_vc); i < n; i++)// điều kiện tìm xem bên nhào nhiều vật cản hơn để né bên đó ra
		{


			if (p[i].td.x < car.td.x&&car.td.x>1)
				trai++;
			if (p[i].td.x > car.td.x&&car.td.y<CHIEU_RONG - 1)
				phai++;

		}


		if (phai > trai)
		{
			car.td.x--;
		}
		if (trai > phai)
		{
			car.td.x++;
		}
		if (trai == phai)// khi 2 bên có số vật cản bằng nhau thì ưu tiên né vc gần nhất
		{
			if (p[vcgannhat(car, p, list_vc)].td.x < car.td.x && (car.td.x > 1) && (car.td.x < CHIEU_RONG - 1))
				car.td.x++;
			if (p[vcgannhat(car, p, list_vc)].td.x > car.td.x && (car.td.x > 1) && (car.td.x < CHIEU_RONG - 1))
				car.td.x--;
		}

		free(p);
	}


}
