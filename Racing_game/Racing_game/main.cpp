
//USING REFERENCE TO AVOID COPY STRUCT

#include "Functions.h"

#include "Diem.h"
#include "Guide.h"

#include "Car.h"
#include "Barrier.h"
#include "Bullet.h"
#include "Item.h"
#include "AI.h"
#include "Level.h"

Cell map[CHIEU_DAI][CHIEU_RONG];

Car car;
//Barrier vc5;

std::list <Barrier> list_vc;		//dslk dùng để lưu các vật cản

int dan;	//so vien dan co the ban
std::list <Bullet> list_dan;		//nhung vien dan da duoc ban ra

std::list <Item> list_item;		

Level stats;	//stat luu tru nhung thu nhu level, diem, ti le ra vat can, so vat can toi da, ...

//Khoi tao lai xe, vat can, dan, diem, map
void khoiTao()
{
	srand(time(NULL));
	list_vc.clear();
	list_dan.clear();
	list_item.clear();

	stats.diem = 0;
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
	list_item.clear();	// tranh memory leak

	//In "game over".
	gotoXY(CHIEU_RONG + 6, CHIEU_DAI / 2);
	printf("Game Over!\n");
	gotoXY(CHIEU_RONG + 2, CHIEU_DAI / 2 + 1);
	printf("Press Enter to back");

	while (_getch() != 13);

	system("cls");

	Record player;		//lưu tên và điểm người đangg chơi.
						//lấy tên người chơi
	printf("Your score: %u\n", stats.diem);
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
	player.score = stats.diem;

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
	if (GetAsyncKeyState(VK_LEFT))
	{
		moveCar(car, MOVE_LEFT);
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		moveCar(car, MOVE_RIGHT);
	}
	if (GetAsyncKeyState(VK_UP))
	{
		moveCar(car, MOVE_UP);
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		moveCar(car, MOVE_DOWN);
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
	updateLevelStats(stats);

	if (!updateBarriers(list_vc, car, stats))		//=> updateBarriers false khi vat can va cham vao xe 
		return false;							//=> game over

	updateBullets(list_dan, list_vc, car, dan);		//dan

	updateItems(list_item, car, stats.diem, dan, list_vc);			//	item

	
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
	drawBulletsOnBuffer(list_dan, map, LIGHT_YELLOW);

	drawItemsOnBuffer(list_item, map, YELLOW);

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

	// dung de kiem tra stats
	// ban chinh thuc se ko co
	const char *content[] = { "LEVEL %d", "Score: %3d", "Sleep time: %3d", "Max Barrier: %3d",
		"Rate generate barrier: %3d", "Max Amplitude: %3d", "Rate Fluctuation: %3d", "Bullet: %3d" };
	int stat[] = { stats.level, stats.diem, stats.sleep_time, stats.max_barrier, 
				stats.rate_generate_barrier, stats.max_amplitude,stats.rate_fluctuation, dan};
	int n = 8;
	showStats(content, stat, n, CHIEU_RONG + 1, 0);
}

//Ham thuc hien tro choi, bien auto_play mac dinh la false
//play(true) => chuc nang tu dong choi
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

		Sleep(stats.sleep_time);
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

