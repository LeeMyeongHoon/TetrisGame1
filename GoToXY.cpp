#include <Windows.h>

#include "GoToXY.h"

void GoToXY(const int x, const int y)
{
	static const int originX = 20;
	static const int originY = 25;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ (short)(2 * (originX + x)) ,(short)(originY - y) });
}