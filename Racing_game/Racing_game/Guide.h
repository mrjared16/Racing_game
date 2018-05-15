#pragma once

#include "Functions.h"
#define PATH_GUIDE "res/Guide.txt"

void huongdan()
{
	//mở file được thiết lập sẵn và in ra màn hình.
	system("cls");		//xóa màn hình ở giao diện trước.
	FILE *fin;
	fopen_s(&fin, PATH_GUIDE, "r");
	char c;
	while ((c = getc(fin)) != EOF)
	{
		putchar(c);
	}
	fclose(fin);
}