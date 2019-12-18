#include <windows.h>
#include <cmath>
#include <objidl.h>
#include <gdiplus.h>
#include <iostream>
#include <string>
#include <gdiplusstringformat.h>
#include "Plot.h"
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

PLFLT func(PLFLT a)
{
	return a*a;
}

int main()
{
	std::vector<PLFLT> x = { 1,2,3 };
	std::vector<PLFLT> y = { 1,4,9 };
	HWND hWnd = GetConsoleWindow();
	HDC hDC = GetDC(hWnd);

	GdiplusStartupInput gdiplusStartupInput;

	//gdi+ token
	ULONG_PTR gdiplusToken;

	//initialize GDI+
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


	Graphics graphics(hDC);

	Rect rect(50, 50, 450, 350);
	Plot plt(rect);
	plt.env(graphics, -1, 1, -1, 1);
	//plt.plot(graphics, x, y);
	plt.plot(graphics, -1, 1, func, 0.01);
	plt.xlabel(graphics, "x");
	plt.ylabel(graphics, "fun y .....");
	plt.lab(graphics, "Test library plot");
	
	std::cin.ignore();
}
