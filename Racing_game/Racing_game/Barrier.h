#pragma once
#include "Functions.h"

#define NORMAL 0
#define GOT_SHOT 1
#define MAX_BARRIER 4

//Ham tao hinh dang vat can
void setBarrierAppearance(Barrier &vc)
{
	//quy định mảng 3*3.
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i != 1 && j == 1) {
				vc.hd_vc[i][j] = ' ';
			}
			else {
				//Vật cản sau khi đâm sẽ mờ và mất.
				//trung dan = 176;
				vc.hd_vc[i][j] =  vc.state == GOT_SHOT ? 176 : 219;
				//co the tuy bien thanh switch
			}
		}
	}
}

//Ham khoi tao vat can: vi tri, hinh dang
void khoiTaoBarrier(Barrier &vc)
{
	// bỏ 2 khung hai bên nên vật cản có x nhỏ nhẩt là 2, lớn nhất là chiều rộng-3.
	vc.td.y = -3;
	vc.td.x = random(2, CHIEU_RONG - 3);
	setBarrierAppearance(vc);
}


//Ham kiem tra va cham vat can va XE
bool barrierVaChamCar(Barrier &vc, Car &car)
{
	int dx = abs(car.td.x - vc.td.x);
	int dy = abs(car.td.y - vc.td.y);

	return (dx < 3 && dy < 3);	//xe va cham vat can
}


//Ham sinh vat can
void barrierGenerator(std::list <Barrier> &listvc)
{
	Barrier vc_new;
	if (listvc.empty())	//them vat can dau tien
	{
		khoiTaoBarrier(vc_new);
		listvc.push_back(vc_new);
		return;
	}

	int i = random(0, 5);

	//cần update để tránh hiện tượng trùng, && listvc.front().td.y>1chỉ là biện pháp tạm thời.
	if (listvc.size() < MAX_BARRIER && i == 2 && listvc.back().td.y > 1 && listvc.front().td.y > 1)
	{
		khoiTaoBarrier(vc_new);
		listvc.push_back(vc_new);
		//thêm 1 vật cản vào list, để hàm update và hàm hiện thị sử dụng.
		//Bình thường ban đầu list chỉ có 4 vật cản được tạo ra và tái tạo lại. 
		//Nhưng khi bị đạn bắn thì hàm này thật sự công dụng(tốt hơn mảng).
		//khi bị trúng đạn, vật cản đó sẽ bị hủy, và size<4, sẽ có 1 vật cản khác được tạo ra và chèn vào cuối.
	}
}

//Ham update trang thai, vi tri vat can
//Tra ve false neu vat can RA KHOI MAP hoac TRUNG DAN=> remove
bool updateBarrier(Barrier &vc, Car &car, int &diem)
{

	//trung dan || ra ngoai man hinh
	if (vc.state == 1 || vc.td.y == CHIEU_DAI)
	{
		diem += vc.state == GOT_SHOT ? 2 : 1;	//dan ban trung cho 2 diem
		return false;
	}

	vc.td.y++;	//vat can di chuyen xuong

	/*Test AI
	//vật cản đuổi theo xe, hàm random có thể chỉnh sửa để tiện cho việc tự động hóa, vì nếu nó đuổi theo xe 100% thì auto thua.
	int k = random(1, 7 - (diem / 20));
	if (k == 1)
	{
		if (vc.td.x > car.td.x)
			vc.td.x--;
		if (vc.td.x < car.td.x)
			vc.td.x++;
	}
	*/
	return true;
}


//Update trang thai cua TAT CA vat can
//Tra ve false khi vat can VA CHAM VAO XE => game over
bool updateBarriers(std::list <Barrier> &listvc, Car &car, int &diem)
{
	std::list <Barrier>::iterator cursor;

	//sinh vat can
	barrierGenerator(listvc);

	//listvc da co it nhat 1 vat can
	for (cursor = listvc.begin(); cursor != listvc.end(); )	//chuyen cursor ++ xuong duoi de tranh loi khi erase
	{
		if (!updateBarrier(*cursor, car, diem)) {		//di chuyen vat can, tra ve true khi vat can ra khoi ngoai man hinh => remove vat can
			cursor = listvc.erase(cursor);
		}
		else {
			if (barrierVaChamCar(*cursor, car))	//nếu game over thì trả về true để hủy vòng lặp bên ngoài.
				return false;
			cursor++;
		}
	}
	
	return true;
}


//Ham ve vat can len map
void drawBarrierOnBuffer(Barrier &vc, Cell map[CHIEU_DAI][CHIEU_RONG], int color)
{
	//tách hàm để dễ quản lí.
	int x_vc = vc.td.x;
	int y_vc = vc.td.y;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (y_vc + i - 1 >= 0 && y_vc + i - 1 < CHIEU_DAI)
			{
				map[y_vc + i - 1][x_vc + j - 1].character = vc.hd_vc[i][j];
				map[y_vc + i - 1][x_vc + j - 1].color = color;		//màu đỏ
			}
		}
	}

}

//Ham ve TAT CA vat can len map
void drawBarriersOnBuffer(std::list <Barrier> &listvc, Cell map[CHIEU_DAI][CHIEU_RONG], int color)
{
	std::list <Barrier>::iterator cursor;
	//in vat can len map.
	for (cursor = listvc.begin(); cursor != listvc.end(); cursor++)
	{
		drawBarrierOnBuffer(*cursor, map, color);
	}
}
