#pragma once

#include "Functions.h"
#define PATH_HIGHSCORES "res/HighScores.txt"

//updateFileDiemCao() => reset diem
//updateFileDiemCao(&dc) => update dc

//Doc thong tin nguoi choi tu file
bool readRecord(FILE *stream, Record &player)
{
	if (fgets(player.name, 26, stream) == NULL)
		return false;	//doc 1 dong => bao gom ca ten va user

	char* context = NULL;
	char *token = strtok_s(player.name, ",", &context);		//su dung strtok de tach name va diem
	
	if (token == NULL)
		return false;

	player.score = atoi(strtok_s(NULL, ",", &context));
	return true;
}

//Ham cap nhat thong tin diem cao vao file
void updateFileDiemCao(list <Record> *dc = NULL)
{
	//Nếu người dùng thiết lập thì reset lại điểm là là player12345....
	FILE *fout;
	fopen_s(&fout, PATH_HIGHSCORES, "w");

	if (dc == NULL)
	{
		for (int i = 0; i < 5; i++)
		{
			fprintf(fout, "Player%d,0\n", i + 1);
		}
	}
	else
	{
		list <Record>::iterator cursor1;
		// do da loai bo tu truoc nen chi co 5 phan tu
		for (cursor1 = dc->begin(); cursor1 != dc->end(); cursor1++)
		{
			fprintf(fout, "%s,%u\n", cursor1->name, cursor1->score);
		}
	}

	fclose(fout);
}

//Ham cap nhat top 5 diem cao
bool updateDiemCao(Record &player)
{
	//mở file.
	FILE *fin;
	fopen_s(&fin, PATH_HIGHSCORES, "r");

	Record temp;	//bien tam de doc, dua vao list
	list <Record> dc;

	//duyệt file đưa vào list.
	while (!feof(fin))
	{
		if (readRecord(fin, temp))
			dc.push_back(temp);
	}

	bool add = false;
	list <Record>::iterator cursor1;

	//tim vi tri chen diem cao (neu co)
	for (cursor1 = dc.begin(); cursor1 != dc.end(); cursor1++)
	{
		if (player.score > (*cursor1).score)
		{
			dc.insert(cursor1, player);
			add = true;
			break;
		}
	}

	fclose(fin);

	if (add){
		dc.pop_back();	//loai bo thanh phan thu 6
		updateFileDiemCao(&dc);	//update
		//printf("Add thanh cong");
	}

	dc.clear();		//giai phong bo nho tranh memory leak
	return add;
}

//Ham xuat muc top 5 diem cao
void xuatDiemCao()
{
	system("cls");		//xóa màn hình giao diện trước.
	setColor(WHITE);
						//File DiemCao lưu danh sách điểm cao, chỉ cần mở file và xuất ra màn hình.
	FILE *fin;
	fopen_s(&fin, PATH_HIGHSCORES, "r");

	if (fin == NULL)	//ko tim thay file
	{
		updateFileDiemCao();	//create new one
		fopen_s(&fin, PATH_HIGHSCORES, "r");	//re-open
	}

	printf("\tThe Hall of Fame:\n\n");

	int num = 0;
	Record player;
	
	
	while (!feof(fin))
	{
		//ko nen su dung scanf de doc string
		if (readRecord(fin, player))
		{
			gotoXY(8, num + 3);
			printf("No.%d:  ", ++num);
			gotoXY(16, num + 2);
			printf("%s", player.name);
			gotoXY(41, num + 2);
			printf("<>");
			gotoXY(43, num + 2);
			printf("%3u", player.score);
		}
	}

	fclose(fin);
}

//Ham in menu Hall of Game va hieu ung dong
void scoreMenu()
{
	system("cls");		//xoá màn hình giao diện trước, đưa cho người dùng nhiều sự lựa chọn.
	gotoXY(8, 0);
	setColor(WHITE);
	printf("Welcome to Hall of Fame\n");

	
	int index = 1;
	int n_label = 3;
	const char *label[] = { "I want to see it.", "Reset HOF.", "Back." };

	MenuFuntions(label, n_label, index, LIGHT_RED, 8, 2);

	system("cls");

	switch (index) {
		case 1:
			xuatDiemCao();			//nếu 1 thì chuyển đến mục xuất điểm cao
			break;
		case 2:
			updateFileDiemCao();	//ham updateFileDiemCao ko co doi so se reset diem
			gotoXY(8, 4);
			printf("High scores reset.\n");
			break;
		case 3:
			mainMenu();		//trở về

	}

	printf("\n");
	showBackButton(8, 8);

	scoreMenu();	//ép buộc người dùng nhấn Enter để trở về mục điểm cao, nếu không không chạy.
}