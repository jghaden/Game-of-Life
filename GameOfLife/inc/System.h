#pragma once

#include "PCH.h"

void gotoXY(int x, int y);
inline void WriteAt(int x, int y, char ch)
{
	gotoXY(x, y);
	std::cout << ch;
}

void ShowConsoleCursor(bool showFlag);

void SetWindowSize(int w, int h);
void SetFontSize(int w, int h);