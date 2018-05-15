#include"function.h"
ACell map[CHIEU_DAI][CHIEU_RONG];
Xe car;
Tien t;
VatCan vc5;
int diem = 0, dan = 1;
list <VatCan> listvc;		//dslk dùng để lưu các vật cản
list <VatCan>::iterator cursor, tam;
list <Record> dc;		//dslk dùng để lưu điểm cao rồi lưu vào file.
list <Record>::iterator cursor1;
list <Dan> listdan;
list <Dan>::iterator cursor2, tam2;
list <Tien> listtien;//dslk lưu tiền và vật phẩm.
list <Tien>::iterator cursor3;

Record player;		//lưu tên và điểm người đangg chơi.
int key;

void choimoi();
void giaodiendiemcao();
void giaodienbandau();

void thietlaplaidc()
{
	//ý tưởng: mở file DIEMCAO(cái file ghi điểm) để tái tạo lại file.
	//Nếu người dùng thiết lập thì reset lại điểm là là player12345....
	FILE *fin = fopen("DIEMCAO.txt", "w");
	//truyền vào file.
	for (int i = 1;i < 6;i++)
	{
		fprintf(fin, "Player%d 0", i);
	}
	fclose(fin);
	system("cls");		//xóa giao diện của mục điểm cao.
	cout << "High scores reset." << endl;
	colorit(12);
	cout << "\nBack.";
	while (_getch() != 13);
	giaodiendiemcao();	//ép buộc người dùng nhấn Enter để trở về mục điểm cao, nếu không không chạy.
}

void saochepfile()
{
	//file DIEMCAOtemp xem như 1 file tạm để lưu các giá trị điểm cao mớii cập nhật
	//ta phải chuyển dữ liệu này về file DIEMCAO - file lưu điểm cao gốc.
	FILE *fin = fopen("DIEMCAOtemp.txt", "r");
	FILE *fout = fopen("DIEMCAO.txt", "w");
	char p[100];
	int i = 0;
	while (!feof(fin))
	{
		fscanf(fin, "%c", &p[i++]);
	}
	//Nhẽ ra có thể viết fprintf(fout, "%c", p[i]) lên trên
	//nhưng vì cái giá trị cuối là rác nên t tách ra.
	for (int j = 0;j < i - 1;j++)
	{
		fprintf(fout, "%c", p[j]);
	}
	fclose(fin);
	fclose(fout);
}

void hinhdangxe(Xe &car)
{
	//quy định các giá trị trong mảng 3*3
	car.hd_xe[0][0] = car.hd_xe[2][0] = car.hd_xe[0][2] = car.hd_xe[2][2] = 'o';
	car.hd_xe[0][1] = car.hd_xe[2][1] = ' ';
	car.hd_xe[1][0] = car.hd_xe[1][2] = ':';
	car.hd_xe[1][1] = 'X';
}

void hinhdangvcsaukhitrungdan(VatCan &vc)
{
	//Vật cản sau khi đâm sẽ mờ và mất.
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i != 1 && j == 1) {
				vc.hd_vc[i][j] = ' ';
			}
			else {
				vc.hd_vc[i][j] = 176;
			}
		}
	}
}

void hinhdangvc(VatCan &vc)
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
				vc.hd_vc[i][j] = 219;
			}
		}
	}
}

void huongdan()
{
	//mở file được thiết lập sẵn và in ra màn hình.
	system("cls");		//xóa màn hình ở giao diện trước.
	FILE *fin = fopen("Guilde.txt", "r");
	while (!feof(fin))
	{
		char a;
		fscanf(fin, "%c", &a);
		printf("%c", a);
	}

	gotoXY(16, 7);
	colorit(12);
	cout << "Back.";
	while (_getch() != 13);

	giaodienbandau();		//ép buộc người dùng nhấn Enter để trở về menu chính.

	fclose(fin);
}

void xuatdiemcao()
{
	//File DIEMCAO lưu danh sách điểm cao, chỉ cần mở file và xuất ra màn hình.
	FILE *fin = fopen("DIEMCAO.txt", "r");
	system("cls");		//xóa màn hình giao diện trước.
	printf("\tThe Hall of Fame:\n");
	char name[26];
	int score = 0;
	int num = 0;
	while (!feof(fin))
	{
		printf("\tNo.%d:  ", ++num);
		fscanf(fin, "%s", &name);		//tách tên từ file
		printf("\t%s: ", name);
		fscanf(fin, "%d", &score);		//tách điểm từ file
		printf("\t%d\n", score);
	}
	fclose(fin);

	colorit(12);
	printf("\n\tBack.");
	while (_getch() != 13);

	giaodiendiemcao();		//ép buộc người dùng nhấn Enter để trở về giao diện trước.
}

void giaodienbandau()
{
	system("cls");		//xóa màn hình, ví dụ người dùng từ mục điểm cao trở ra, pbải xóa màn hình của giao diện điểm cao.
						//nếu người dùng không trở ra từ ""Tiếp tục'" thì không có dòng Nhan 9 de tiep tuc.
	key = 0;

	while (key != 13)
	{
		if (listvc.size() == 0)
		{
			//system("cls");
			gotoXY(8, 0);
			colorit(15);
			printf("RACING GAME");

			colorit(15);		//Màu trắng
			if (index == 1)
			{
				colorit(12);		//Nếu được chon sẽ chuyển thành màu đỏ
			}
			gotoXY(8, 2);
			cout << "New game." << endl;

			colorit(15);
			if (index == 2)
			{
				colorit(12);
			}
			gotoXY(8, 3);
			cout << "High scores." << endl;

			colorit(15);
			if (index == 3)
			{
				colorit(12);
			}
			gotoXY(8, 4);
			cout << "CPU vs CPU." << endl;

			colorit(15);
			if (index == 4)
			{
				colorit(12);
			}
			gotoXY(8, 5);
			cout << "Help." << endl;

			colorit(15);
			if (index == 5)
			{
				colorit(12);
			}
			gotoXY(8, 6);
			cout << "Exit." << endl;

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
		else
		{
			//system("cls");
			colorit(15);
			if (index == 0)
			{
				colorit(12);
			}
			gotoXY(8, 1);
			cout << "Resume" << endl;

			colorit(15);
			if (index == 1)
			{
				colorit(12);
			}
			gotoXY(8, 2);
			cout << "New game." << endl;

			colorit(15);
			if (index == 2)
			{
				colorit(12);
			}
			gotoXY(8, 3);
			cout << "High scores." << endl;

			colorit(15);
			if (index == 3)
			{
				colorit(12);
			}
			gotoXY(8, 4);
			cout << "CPU vs CPU." << endl;

			colorit(15);
			if (index == 4)
			{
				colorit(12);
			}
			gotoXY(8, 5);
			cout << "Help." << endl;

			colorit(15);
			if (index == 5)
			{
				colorit(12);
			}
			gotoXY(8, 6);
			cout << "Exit." << endl;

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
				index = 0;
			}
			if (index == -1)
			{
				index = 5;
			}
		}
	}


	//điều kiện chạy thuật toán.
	if (index == 1) choimoi();
	if (index == 2) giaodiendiemcao();
	if (index == 4) huongdan();
	if (index == 5 || index == 0)  return;
}

void updatediemcao()
{
	//mở file.
	FILE *fin = fopen("DIEMCAO.txt", "r");
	FILE *fout = fopen("DIEMCAOtemp.txt", "w");
	Record temp;
	//duyệt file đưa vào list.
	while (!feof(fin))
	{
		fscanf(fin, "%s %d", &temp.name, &temp.score);
		dc.push_back(temp);
	}
	//chèn player vào list nếu lớn hơn 1 điểm cao.

	for (cursor1 = dc.begin();cursor1 != dc.end();cursor1++)
	{
		if (player.score > (*cursor1).score)
		{
			dc.insert(cursor1, player);
			break;
		}
	}
	//vòng lặp đưa list điểm vào file, đưa 5 thằng cao nhất.
	int dem = 0;
	for (cursor1 = dc.begin();cursor1 != dc.end();cursor1++)
	{
		if (dem < 5)
		{
			fprintf(fout, " %s %d", (*cursor1).name, (*cursor1).score);
		}
		dem++;
	}
	//đóng file.
	fclose(fin);
	fclose(fout);
	//xóa list, trường hợp người chơi muốn chơi lại.
	dc.clear();
	//chuyển danh sách điểm cao mới vào file ban đầu.
	saochepfile();
}

void giaodiendiemcao()
{
	system("cls");		//xoá màn hình giao diện trước, đưa cho người dùng nhiều sự lựa chọn.
	gotoXY(8, 0);
	colorit(15);
	cout << "Welcome to Hall of Fame" << endl;
	key = 0;
	index = 1;
	while (key != 13)		//Khác Enter
	{
		//system("cls");		
		colorit(15);		//Màu trắng
		if (index == 1)
		{
			colorit(12);		//Nếu được chon sẽ chuyển thành màu đỏ
		}
		gotoXY(8, 2);
		cout << "I want to see it." << endl;

		colorit(15);
		if (index == 2)
		{
			colorit(12);
		}
		gotoXY(8, 3);
		cout << "Reset HOF." << endl;

		colorit(15);
		if (index == 3)
		{
			colorit(12);
		}
		gotoXY(8, 4);
		cout << "Back.";

		key = _getch();
		if (key == 80)
		{
			++index;
		}
		else if (key == 72)
		{
			--index;
		}
		if (index == 4)
		{
			index = 1;
		}
		if (index == 0)
		{
			index = 3;
		}
	}

	if (index == 1) xuatdiemcao();		//nếu 1 thì chuyển đến mục xuất điểm cao
	if (index == 2) thietlaplaidc();		//tương tự
	if (index == 3) giaodienbandau();		//trở về

}

bool nhanphim()
{
	//Di chuyển xe và tạm dừng game.
	if (GetAsyncKeyState(VK_LEFT) && car.td.x  > 2)
	{
		car.td.x--;
	}
	if (GetAsyncKeyState(VK_RIGHT) && (car.td.x + 1) + 1 <= CHIEU_RONG - 2)
	{
		car.td.x++;
	}
	if (GetAsyncKeyState(VK_UP) && (car.td.y > 1))
	{
		car.td.y--;
	}
	if (GetAsyncKeyState(VK_DOWN) && (car.td.y < CHIEU_DAI - 2))
	{
		car.td.y++;
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		return true;
	}
	else
	{
		return false;		//để tạm dừng game
	}
}

bool timkhoangtrong()
{
	//hàm này dùng để tìm xem có khoảng trống giữa 2 vc khôg,
	//để chèn tiền và vật phẩm vào, tránh hiện tượng trùng.
	for (cursor = listvc.begin();cursor != listvc.end();cursor++)
	{
		if ((*cursor).td.y < 1) return false;
	}
	return true;
}

void xacsuatratien()
{
	int i = random(0, 20);
	if (i == 1 && timkhoangtrong() && listtien.size() < 2)
	{
		Tien t;
		t.td.x = random(2, CHIEU_RONG - 3);
		t.td.y = -1;
		if (i % 4 == 1) t.a = 233;
		else
			t.a = 36;
		listtien.push_back(t);
	}
}

void xacsuatradan()
{
	//chỉ cho phép bắn 20 viên, và khoảng cách mỗi viên là 4 đơn vị.
	if (listdan.size() < 20
		&& (listdan.front().td.y + 60) % 4 == 1)
	{
		Dan dan1;
		dan1.td.x = car.td.x;
		dan1.td.y = car.td.y - 3;
		listdan.push_back(dan1);
		//chèn 1 viên vào list, để hàm update trạng thái và hiện thị sử dụng đưa lên màn hình.
	}
}

void xacsuatravc()
{
	int i = random(0, 10);
	//cần update để tránh hiện tượng trùng, && listvc.front().td.y>1chỉ là biện pháp tạm thời.
	if (listvc.size()<4 && i == 2 && listvc.back().td.y>1 && listvc.front().td.y>1)
	{
		VatCan vc1;
		vc1.td.y = -2;
		vc1.td.x = random(2, CHIEU_RONG - 3);
		hinhdangvc(vc1);
		listvc.push_back(vc1);
		//thêm 1 vật cản vào list, để hàm update và hàm hiện thị sử dụng.
		//Bình thường ban đầu list chỉ có 4 vật cản được tạo ra và tái tạo lại. 
		//Nhưng khi bị đạn bắn thì hàm này thật sự công dụng(tốt hơn mảng).
		//khi bị trúng đạn, vật cản đó sẽ bị hủy, và size<4, sẽ có 1 vật cản khác được tạo ra và chèn vào cuối.
	}
}

void khoiTao()
{
	srand(time(NULL));
	//xe được khởi tạo cuối dường đua
	car.td.x = CHIEU_RONG / 2;
	car.td.y = CHIEU_DAI - 2;
	hinhdangxe(car);

	// bỏ 2 khung hai bên nên vật cản có x nhỏ nhẩt là 2, lớn nhất là chiều rộng-3.
	// đưa vc đầu tiên vào list.
	VatCan vc;
	vc.td.x = random(2, CHIEU_RONG - 3);
	vc.td.y = -2;
	hinhdangvc(vc);
	listvc.push_back(vc);


	//tạo mảng.
	for (int i = 0; i < CHIEU_DAI; i++)
	{
		for (int j = 0; j < CHIEU_RONG; j++)
		{
			map[i][j].character = ' ';
		}
	}
}

int updateTien(Tien &t)
{
	if (t.td.y == CHIEU_DAI + 1)
	{
		return 1;
	}
	else
		t.td.y++;
	int dx = abs(car.td.x - t.td.x);
	int dy = abs(car.td.y - t.td.y);
	if (dx < 2 && dy < 2)
	{
		return 2;
	}
	return 0;
}

bool updatevc(VatCan &vc)
{
	if (vc.td.y == CHIEU_DAI)
	{
		diem++;
	}
	//khởi tạo lại vật cản hoặc tăng y.
	if (vc.td.y == CHIEU_DAI + 1)
	{
		vc.td.y = -2;
		vc.td.x = random(2, CHIEU_RONG - 3);
	}
	else
	{
		vc.td.y++;
	}

	//vật cản đuổi theo xe, hàm random có thể chỉnh sửa để tiện cho việc tự động hóa, vì nếu nó đuổi theo xe 100% thì auto thua.
	int k = random(1, 7 - (diem / 20));
	if (vc.td.x > car.td.x && k == 1)
	{
		vc.td.x--;
	}
	if (vc.td.x < car.td.x && k == 1)
	{
		vc.td.x++;
	}

	/*test, vật cản chuyển động qua lại nhưng nhìn nó rối mắt quá.
	int k = random(1, 5);
	if (k == 1 && vc.td.x > 2) vc.td.x--;
	if (k == 5 && vc.td.x < CHIEU_RONG - 3) vc.td.x++;
	*/

	//game over,trả ra true để break vòng lặp bên ngoài.
	int dx = abs(car.td.x - vc.td.x);
	int dy = abs(car.td.y - vc.td.y);
	if (dx < 3 && dy < 3)
	{
		return true;
	}
	return false;

}

bool vatcantrungdan()
{
	//ý tưởng: duyệt đạn và vật cản xem có nào đâm trúng nhau không
	//nếu có xóa chúng khỏi list (như vây chúng sẽ biến mất trong game)
	//vòng for duyệt list đạn
	for (cursor2 = listdan.begin(); cursor2 != listdan.end(); cursor2++)
	{
		int x2 = (*cursor2).td.x;int y2 = (*cursor2).td.y;		//quy định để tiện tính toán
		for (cursor = listvc.begin();cursor != listvc.end();cursor++)		//vòng for duyệt vật cản.
		{
			int x1 = (*cursor).td.x, y1 = (*cursor).td.y;

			//nếu đạn chạm xe thì đạn và xe biến mất.
			if (abs(x1 - x2) < 2 && abs(y1 - y2) < 2 && y1>-2)		//>-2 để khi ta thấy dc vật cản mới công nhận vc trúng đạn.
			{
				listvc.erase(cursor);		//xóa vc
				listdan.erase(cursor2);		//xóa đạn
				diem = diem + 2;
				vc5.td.x = x1;
				vc5.td.y = y1;
				hinhdangvcsaukhitrungdan(vc5);		//hàm này chỉ màu mè(đồ họa), vật cản sẽ bị nhạt đi trước khi biến mất.
				return true;		//cái này rất quan trọng, thiếu sẽ lỗi.
									//lí do: vì co vc trúng đạn, vc và đạn xe bị xóa khỏi list, nếu tiếp tục duyệt mảng sẽ lỗi, 
									//bất cập: nếu trong 1 lần có 2 vc bị trúng đạn thì chỉ xử lí cái vc đầu, cái vc còn lại đợi vòng lặp sau. vì
									//chúng diễn ra nhanh nên người dùng sẽ không thấy được.
			}
		}
	}
	return false;
}

void invclenmap(VatCan &vc)
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
				map[y_vc + i - 1][x_vc + j - 1].color = 14;		//màu đỏ
			}
		}
	}
}

bool updateTrangThai()
{
	if (listvc.size() == 0)
	{
		//nếu người chơi lần đầu thì size !=0 do hàm khởi tạo
		//nhưng nếu chơi lại thì list bị xóa,phải khỏi tạo lại nhờ hàm này
		VatCan vc1;
		vc1.td.y = -2;
		vc1.td.x = random(2, CHIEU_RONG - 3);
		hinhdangvc(vc1);
		listvc.push_back(vc1);
	}
	for (cursor = listvc.begin();cursor != listvc.end();cursor++)
	{
		if (updatevc(*cursor)) return true;		//nếu game over thì trả về true để hủy vòng lặp bên ngoài.
		xacsuatravc();		//nếu chưa đủ 4 cái vc thì thêm.
	}

	xacsuatratien();
	if (listtien.size() != 0)
	{
		for (cursor3 = listtien.begin();cursor3 != listtien.end();cursor3++)
		{
			if (updateTien(*cursor3))
			{
				//listtien.erase(cursor3);
				if(updateTien(*cursor3)==2) diem = diem + 2;
			}
		}
	}
	if (dan == 1)// điều kiện bắn đạn,khai báo đầu bài.
	{
		if (listdan.size() == 0)//nếu list rỗng thì phải khởi tạo.
		{
			Dan dan1;
			dan1.td.x = car.td.x;
			dan1.td.y = car.td.y - 3;
			listdan.push_back(dan1);
		}
		else//nếu không rỗng thì chạy dòng for để đạn bay lên.
		{
			for (cursor2 = listdan.begin();cursor2 != listdan.end();cursor2++)
				//sau mỗi vòng lặp đạn bay lên.
				(*cursor2).td.y--;
			xacsuatradan();
		}
		if (listdan.back().td.y < 0)
		{
			listdan.clear();
			dan = 0;
		}//xóa list đạn, và đổi điều kiện để đạn k bắn ra nữa.
	}
	if (vatcantrungdan()) invclenmap(vc5);
	return false;
	//kết thúc hàm sẽ trả về true, false (game over).
}

void hienthi()
{
	ShowConsoleCursor(false);
	// Vẽ xe và vật cản lên map
	//In hình dạng xe lên mảng 2 chiều m.
	int x_xe = car.td.x;
	int y_xe = car.td.y;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			map[y_xe + i - 1][x_xe + j - 1].character = car.hd_xe[i][j];
			map[y_xe + i - 1][x_xe + j - 1].color = 10;		//Màu trắng
		}
	}
	//in vat can len map.
	for (cursor = listvc.begin();cursor != listvc.end();cursor++)
	{
		invclenmap(*cursor);
	}
	//in tien len map.
	for (cursor3 = listtien.begin();cursor3 != listtien.end();cursor3++)
	{
		map[(*cursor3).td.y][(*cursor3).td.x].character = (*cursor3).a;
		map[(*cursor3).td.y][(*cursor3).td.x].color = 15;
	}
	//in dan len map neu co.
	for (cursor2 = listdan.begin();cursor2 != listdan.end();cursor2++)
	{
		if ((*cursor2).td.y > -1)
		{
			map[(*cursor2).td.y][(*cursor2).td.x].character = 248;
			map[(*cursor2).td.y][(*cursor2).td.x].color = 4;
		}
	}

	// Vẽ khung cho map.
	for (int i = 0; i < CHIEU_DAI; i++)
	{
		map[i][0].character = 179;
		map[i][0].color = 11;		//Màu lam
		map[i][CHIEU_RONG - 1].character = 179;
		map[i][CHIEU_RONG - 1].color = 11;
	}
	gotoXY(0, 0);

	// in map
	for (int i = 0; i < CHIEU_DAI; i++)
	{
		for (int j = 0; j < CHIEU_RONG; j++)
		{
			colorit(map[i][j].color);
			putchar(map[i][j].character);

			// Sau khi in reset lại
			map[i][j].character = ' ';
		}
		printf("\n");
	}
	gotoXY(CHIEU_RONG + 1, 0);
	printf("Score: %d", diem);
}

void tamdung()
{
	//khi người dùng nhấn Space tạm dừng sẽ dc gọi
	//ý tưởng, người dùng có 2 lựa chọn
	key = 0;
	while (key != 13)
	{
		key = _getch();
		if (key == 80)
		{
			++index;
		}
		else if (key == 72)
		{
			--index;
		}
		if (index == 3)
		{
			index = 1;
		}
		if (index == 0)
		{
			index = 2;
		}

		gotoXY(CHIEU_RONG + 1, CHIEU_DAI / 2);
		colorit(15);		//Màu trắng
		if (index == 1)
		{
			colorit(12);		//Nếu được chon sẽ chuyển thành màu đỏ
		}
		cout << "Resume.";

		colorit(15);
		if (index == 2)
		{
			colorit(12);
		}
		gotoXY(CHIEU_RONG + 1, CHIEU_DAI / 2 + 1);
		cout << "Back.";
	}
	if (index == 2)
	{
		giaodienbandau();
	}
	//1. nhấn back để trở về giao diện chính, 2. nhân enter để bỏ qua hàm này (nghĩa là tiếp tục).
	gotoXY(CHIEU_RONG + 1, CHIEU_DAI / 2);
	printf("                        ");
	gotoXY(CHIEU_RONG + 1, CHIEU_DAI / 2 + 1);
	printf("                        ");
}

void choimoi()
{
	//xóa list vật cản phòng trường hợp nguòi chơi chơi lại.
	listvc.clear();
	listtien.clear();
	diem = 0;
	khoiTao();
	system("cls");
	while (1) {
		if (nhanphim()) tamdung();		//nếu nhấn Space sẽ tạm dừng.

		if (updateTrangThai())  break;		//game over, dừng vòng lặp.

		hienthi();

		Sleep(100 - 1.5*diem);		//cần sửa nếu tự động hóa. test.
	}

	//lưu điểm
	player.score = diem;

	//xoa list để thỏa điều kiện trong hàm tamdung.
	listvc.clear();

	//In "game over".
	gotoXY(CHIEU_RONG + 6, CHIEU_DAI / 2);
	printf("Game Over!\n");
	gotoXY(CHIEU_RONG + 2, CHIEU_DAI / 2 + 1);
	printf("Press Enter to back");
	while (_getch() != 13);
	system("cls");

	//lấy tên người chơi
	printf("Player name: ");
	scanf("%s", &player.name);

	//đưa vào top player nếu có thể.
	updatediemcao();
	giaodienbandau();
}

int main()
{
	//PlaySound(TEXT("123.wav"), NULL, SND_ASYNC);
	ShowConsoleCursor(false);//không hiện con trỏ lên màn hình.

	giaodienbandau();
	return 0;
}
