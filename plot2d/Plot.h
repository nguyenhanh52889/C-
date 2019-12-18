#pragma once


#include "plotstream.h"
#include <vector>
#include <functional>
#include <windows.h>
#include <cmath>
#include <objidl.h>
#include <gdiplus.h>
#include <iostream>
#include <string>
#include <gdiplusstringformat.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

typedef double   PLFLT;



class Plot
{
	
public:
	//Plot(int bottom=100, int left=100, int right=1100, int top=1100) : bottom(bottom), left(left), right(right), top(top) {
	Plot(Rect rect) : rect(rect) {
	}
	

	void env(Graphics &graphics, PLFLT xmin, PLFLT xmax, PLFLT ymin, PLFLT ymax)
	{
		
		
		//std::cout << rect.GetRight() << " " << rect.GetLeft() << " " << rect.GetTop() 
		//	<< " " << rect.GetBottom() << std::endl;
		//std::cout << x0 << " " << y0;
		pstream = Plotstream(xmin, xmax, ymin, ymax,rect);
	};

	void plot(Graphics &graphics, std::vector<PLFLT> &x, std::vector<PLFLT> &y)
	{

		GraphicsContainer container;
		container = graphics.BeginContainer();

		pstream.plot(graphics, x, y);
		

		graphics.EndContainer(container);
	}

	void plot(Graphics &graphics, PLFLT start, PLFLT end, std::function<PLFLT(PLFLT)> func, PLFLT step=0.01)
	{

		GraphicsContainer container;
		container = graphics.BeginContainer();

		pstream.plot(graphics, start, end, func, step);


		graphics.EndContainer(container);
	}

	void xlabel(Graphics &graphics, const char* string)
	{
		GraphicsContainer container;
		container = graphics.BeginContainer();

		pstream.xlabel(graphics, string);
		graphics.EndContainer(container);
	}

	void ylabel(Graphics &graphics, const char * string)
	{
		GraphicsContainer container;
		container = graphics.BeginContainer();

		pstream.ylabel(graphics, string);


		graphics.EndContainer(container);
	}

	void lab(Graphics &graphics, const char * string)
	{
		GraphicsContainer container;
		container = graphics.BeginContainer();

		pstream.lab(graphics, string);


		graphics.EndContainer(container);
	}

private:
	HWND hWnd;
	HDC hDC;
	int bottom, left, right, top;
	int width;
	int height;
	PLFLT scalex;
	PLFLT scaley;
	GdiplusStartupInput gdiplusStartupInput;
	Rect rect;
	//gdi+ token
	ULONG_PTR gdiplusToken;
	//Graphics graphics;
	Plotstream pstream;
};



