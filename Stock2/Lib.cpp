#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#include "Lib.h"


void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void textcolor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}


void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c)
	{
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}


void type_effect(char *str, int delay)
{
	int i = 0;
	while (str[i] != '\0') printf("%c", str[i]), i++, Sleep(delay);
}


void clearbuffer()
{
	while (kbhit()) getch();
}


void titleLine(const char *title)
{
	printf("\n %s\n", title);
	for (int i = 0; i < 40; i++) printf("¦¬");
	printf("\n");
	return;
}