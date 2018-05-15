
#include "Functions.h"

#include "Diem.h"
#include "Guide.h"

#include "Car.h"
#include "Barrier.h"
#include "Bullet.h"
#include "Coin.h"
#include "AI.h"

Cell map[CHIEU_DAI][CHIEU_RONG];

Car car;
//Barrier vc5;

int diem;

std::list <Barrier> list_vc;		//dslk dùng để lưu các vật cản

int dan;	//so vien dan co the ban
std::list <Bullet> list_dan;		//nhung vien dan da duoc ban ra


//Khoi tao lai xe, vat can, dan, diem, map
void khoiTao()
{
	srand(time(NULL));
	list_vc.clear();
	list_dan.clear();

	diem = 0;
	dan = 0;
	
	//xe được khởi tạo cuối dường đua
	khoiTaoCar(car);

	//tạo map.
	for (int i = 0; i < CHIEU_DAI; i++)
	{
		for (int j = 0; j < CHIEU_RONG; j++)
		{
			map[i][j].character = ' ';
		}
	}
}

//Ham game over
void gameOver() {
	list_vc.clear();	// tranh memory leak
	list_dan.clear();	// tranh memory leak

	//In "game over".
	gotoXY(CHIEU_RONG + 6, CHIEU_DAI / 2);
	printf("Game Over!\n");
	gotoXY(CHIEU_RONG + 2, CHIEU_DAI / 2 + 1);
	printf("Press Enter to back");

	while (_getch() != 13);

	system("cls");

	Record player;		//lưu tên và điểm người đangg chơi.
						//lấy tên người chơi
	printf("Your score: %d\n", diem);
	printf("Player name: ");

	//doc ten player
	while (1)
	{
		fgets(player.name, MAX_PLAYER_NAME, stdin);
		if (strcmp(player.name, "\n") != 0) {
			char *tmp = NULL;
			strtok_s(player.name, "\n", &tmp);
			break;
		}
		printf("You cant enter a NULL. Please try again!\n");
	}

	//lưu điểm
	player.score = diem;

	//đưa vào top player nếu có thể.
	updateDiemCao(player);
		
	xuatDiemCao();		// xuat danh sach diem cao sau khi choi
		
	showBackButton(16, 7);	//Back to main menu
		
	mainMenu();
}

//Ham tam dung
void pause()
{
	//khi người dùng nhấn Space tạm dừng sẽ dc gọi
	//ý tưởng, người dùng có 2 lựa chọn
	int index = 1;
	const char *label[] = { "Resume", "Back"};
	int n_label = 2;
	showMenu(label, n_label, index, LIGHT_RED, CHIEU_RONG + 1, CHIEU_DAI / 2);

	//1. nhấn back để trở về giao diện chính, 2. nhân enter để bỏ qua hàm này (nghĩa là tiếp tục).
	if (index == 1)
	{
		hideMenu(n_label, CHIEU_RONG + 1, CHIEU_DAI / 2);
	}
	if (index == 2)
	{
		mainMenu();
	}
}

//Ham nhan phim
bool getKeyPressed()
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
		pause();	//để tạm dừng game
	}

	return true;
}


//Update cac object nhu vat can, dan
//Tra ve false khi game over
bool updateTrangThai()
{
	if (!updateBarriers(list_vc, car, diem))		//=> updateBarriers false khi vat can va cham vao xe 
		return false;							//=> game over

	//updateCoin(list_tien,)
	//updateItem(list_item,)
	
	updateBullets(list_dan, list_vc, car, dan);		//dan

	//dieu kien tam thoi de test
	if (dieuKienSinhBullet(diem) && dan <= diem / 3)
	{
		dan += diem;
	}

	
	return true;
}

//Hien thi cac vat the
void show()
{
	// ve xe
	drawCarOnBuffer(car, map, LIGHT_GREEN);

	//ve vat can
	drawBarriersOnBuffer(list_vc, map, RED);
	
	//ve dan
	drawBulletsOnBuffer(list_dan, map, YELLOW);



	// Vẽ khung cho map.
	for (int i = 0; i < CHIEU_DAI; i++)
	{
		map[i][0].character = map[i][CHIEU_RONG - 1].character = 179;				// => '|'
		map[i][0].color		= map[i][CHIEU_RONG - 1].color     = LIGHT_CYAN;		//Màu lam
	}

	gotoXY(0, 0);

	// IN MOI THU TREN MAP
	for (int i = 0; i < CHIEU_DAI; i++)
	{
		for (int j = 0; j < CHIEU_RONG; j++)
		{
			setColor(map[i][j].color);
			putchar(map[i][j].character);

			// Sau khi in reset lại
			map[i][j].character = ' ';
		}
		printf("\n");
	}

	gotoXY(CHIEU_RONG + 1, 0);
	printf("Score: %2d", diem);
	gotoXY(CHIEU_RONG + 1, 1);
	printf("Bullet: %2d", dan);
}

void play(bool auto_play)
{
	khoiTao();
	system("cls");

	while (1) {
		if (!getKeyPressed())	//nhan nut back
			return;
		
		if (auto_play)
			tunhanphim(car, list_vc);

		if (!updateTrangThai())
			break;		//game over, dừng vòng lặp.
		
		show();

		DWORD sleep_time = 100 - 1.5 * diem;
		if (sleep_time < 0)
			sleep_time = 0;

		Sleep(sleep_time);
	}
	gameOver();
}

int main()
{
	//PlaySound(TEXT("123.wav"), NULL, SND_ASYNC);

	ShowConsoleCursor(false);//không hiện con trỏ lên màn hình.
	mainMenu();

	return 0;
}

/*bool xacsuatratien()
{
	//chưa dùng đến.
	srand(time(NULL));
	int x = random(2, 300);
	if (x <= CHIEU_RONG - 3 && t.td.y>CHIEU_DAI)
	{
		t.td.x = x;
		t.td.y = -1;
		return true;
	}
	return false;
}




*/