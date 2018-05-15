#include <windows.h>
void gotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

int random(int start, int end)
{
	return start + rand() % (end + 1 - start);
}

//12 = LIGHTRED, 15 = WHITE -----> this.colorit(12); this.colorit(15);
//0 = BLACK, 1 = BLUE
//2 = GREEN, 3 = CYAN
//4 = RED, 5 MAGNETA
//6 = BROWN, 7 = LIGHTGRAY
//8 = DARKGRAY, 9 = LIGHTBLUE
//10 = LIGHTGREEN, 11 = LIGHTCYAN
//13 = LIGHTMAGENTA, 14 = YELLOW