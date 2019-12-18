#ifndef PLOTSTREAM_H
#define PLOTSTREAM_H 

#include <vector>
#include <functional>
#include <windows.h>
#include <cmath>
#include <objidl.h>
#include <gdiplus.h>
#include <iostream>
#include <string>
#include <gdiplusstringformat.h>
#include <string>
#include <stdio.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

typedef double   PLFLT;

enum type_line { point = 0, line = 1 };


class Plotstream
{
public:
	Plotstream() {}
	Plotstream(PLFLT xmin, PLFLT xmax, PLFLT ymin, PLFLT ymax, Rect rect_) : xmin(xmin), xmax(xmax),
		ymin(ymin), ymax(ymax), rect(rect_)
	{
		width = rect.Width;
		height = rect.Height;
		scaley = (ymax - ymin) / (height);
		scalex = (xmax - xmin) / (width);
		if (xmin*xmax < 0)
			x0 = rect.GetLeft() + width * abs(abs(xmin) / (abs(xmax) + abs(xmin)));
		else
			x0 = rect.GetLeft() - width * xmin / (xmax - xmin);
		if (ymin*ymax < 0)
			y0 = rect.GetTop() + height * abs(abs(ymin) / (abs(ymax) + abs(ymin)));
		else
			y0 = rect.GetBottom() + height * ymin / (ymax - ymin);
	};

	void plot(Graphics &graphics, std::vector<PLFLT> &x, std::vector<PLFLT> &y)
	{
		GraphicsContainer container;
		container = graphics.BeginContainer();

		drawAxes(graphics);

		Pen pen(Color(255, 0, 255, 0), 0);
		for (int i = 0; i < x.size() - 1; i++)
		{
			int x1 = x[i] / scalex;
			graphics.DrawLine(&pen, x1, y[i]/scaley, x[i+1]/scalex, y[i+1]/scaley);
		}

		graphics.EndContainer(container);
	};

	void plot(Graphics &graphics, PLFLT start, PLFLT end, std::function<PLFLT(PLFLT)> func, PLFLT step=0.01)
	{
		GraphicsContainer container;
		container = graphics.BeginContainer();

		drawAxes(graphics);

		Pen pen(Color(255, 0, 255, 0), 0);
		for (PLFLT x = start; x < end; x += step)
		{
			int x1 = x / scalex;
			graphics.DrawLine(&pen, x1, func(x) / scaley, (x+step) / scalex, func(x+step) / scaley);
		}
		graphics.EndContainer(container);
	}

	//void xlabel(Graphics &graphics, WCHAR string[])
	void xlabel(Graphics &graphics, const char * lb)
	{
		FontFamily  fontFamily(L"Times New Roman");
		Font        font(&fontFamily, 14, FontStyleRegular, UnitPixel);
		SolidBrush  solidBrush(Color(255, 0, 0, 255));

		StringFormat* pStringFormat = new StringFormat();
		pStringFormat->SetAlignment(StringAlignmentCenter);

		//graphics.TranslateTransform(x0, y0);
		//graphics.RotateTransform(-30.0f);
		const WCHAR *string;
		int nChars = MultiByteToWideChar(CP_ACP, 0, lb, -1, NULL, 0);
		// allocate it
		string = new WCHAR[nChars];
		MultiByteToWideChar(CP_ACP, 0, lb, -1, (LPWSTR)string, nChars);

		graphics.DrawString(
			string,
			nChars,
			&font,
			RectF(rect.X, rect.Y + rect.Height, rect.Width, 50),
			pStringFormat,
			&solidBrush);
	}

	void ylabel(Graphics &graphics, const char * lb)
	{
		FontFamily  fontFamily(L"Times New Roman");
		Font        font(&fontFamily, 14, FontStyleRegular, UnitPixel);		SolidBrush  solidBrush(Color(255, 0, 0, 255));

		StringFormat* pStringFormat = new StringFormat();
		pStringFormat->SetAlignment(StringAlignmentCenter);

		graphics.TranslateTransform(rect.X, rect.Y + rect.Height);
		graphics.RotateTransform(-90.0f);
		Pen pen(Color(255, 0, 255, 0), 0);
		//graphics.DrawLine(&pen, 0, 0, 200, 0);
		//graphics.DrawLine(&pen, 0, 0, 0, 200);
		const WCHAR *string;
		int nChars = MultiByteToWideChar(CP_ACP, 0, lb, -1, NULL, 0);
		// allocate it
		string = new WCHAR[nChars];
		MultiByteToWideChar(CP_ACP, 0, lb, -1, (LPWSTR)string, nChars);

		graphics.DrawString(
			string,
			nChars,
			&font,
			RectF(0, -20, rect.Height, 20),
			pStringFormat,
			&solidBrush);
	}


	void lab(Graphics &graphics, const char * lb)
	{
		FontFamily  fontFamily(L"Times New Roman");
		Font        font(&fontFamily, 14, FontStyleRegular, UnitPixel);
		SolidBrush  solidBrush(Color(255, 0, 0, 255));

		StringFormat* pStringFormat = new StringFormat();

		pStringFormat->SetAlignment(StringAlignmentCenter);
		const WCHAR *string;
		int nChars = MultiByteToWideChar(CP_ACP, 0, lb, -1, NULL, 0);
		// allocate it
		string = new WCHAR[nChars];
		MultiByteToWideChar(CP_ACP, 0, lb, -1, (LPWSTR)string, nChars);
		graphics.DrawString(
			string,
			nChars,  // string length
			&font,
			RectF(rect.X, 0, rect.Width, 20),
			pStringFormat,
			&solidBrush);
	}

private:
	int x0;
	int y0;
	int xmin;
	int ymin;
	int xmax;
	int ymax;
	int width;
	int height;
	Rect rect;
	PLFLT scalex;
	PLFLT scaley;
	void drawAxes(Graphics &graphics)
	{

		Pen pen(Color(255, 255, 0, 0), 0);
		graphics.DrawRectangle(&pen, rect);
		

		Matrix myMatrix(1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
		graphics.SetTransform(&myMatrix);
		//std::cout << x0 << " " << y0 << std::endl;
		graphics.TranslateTransform(x0, y0, MatrixOrderAppend);
		int lo_x = (xmin / scalex);
		int hi_x = (xmax / scalex);
		int lo_y = (ymin / scaley);
		int hi_y = (ymax / scaley);
		graphics.DrawLine(&pen, lo_x, 0, hi_x, 0);
		graphics.DrawLine(&pen, 0, lo_y, 0, hi_y);

		graphics.DrawLine(&pen, 0, 0, 0, 50);
		//std::cout << scalex << " " << scaley << std::endl;
		//std::cout << lo_x << " " << hi_x;
		int stepx = (hi_x - lo_x) / 10;
		int stepy = (hi_y - lo_y) / 10;

		FontFamily  fontFamily(L"Times New Roman");
		Font        font(&fontFamily, 8, FontStyleRegular, UnitPixel);
		
		SolidBrush  solidBrush(Color(255, 0, 0, 255));

		for (int x = 0; x < hi_x; x += stepx)
		{
			PointF      pointF(x, -10);
			x = round(x);
			graphics.DrawLine(&pen, x, -5, x, 5);
			char str[32];

			char lb[10];
			sprintf_s(lb, "%.2f", x*scalex);

			const WCHAR *string;
			int nChars = MultiByteToWideChar(CP_ACP, 0, lb, -1, NULL, 0);
			// allocate it
			string = new WCHAR[nChars];
			MultiByteToWideChar(CP_ACP, 0, lb, -1, (LPWSTR)string, nChars);
			graphics.DrawString(string, -1, &font, pointF, &solidBrush);
		}

		for (int x = 0; x > lo_x; x -= stepx)
		{
			PointF      pointF(x, -10);
			x = round(x);
			graphics.DrawLine(&pen, x, -5, x, 5);
			char str[32];

			char lb[10];
			sprintf_s(lb, "%.2f", x*scalex);

			const WCHAR *string;
			int nChars = MultiByteToWideChar(CP_ACP, 0, lb, -1, NULL, 0);
			// allocate it
			string = new WCHAR[nChars];
			MultiByteToWideChar(CP_ACP, 0, lb, -1, (LPWSTR)string, nChars);
			graphics.DrawString(string, -1, &font, pointF, &solidBrush);
		}

		for (int y = 0; y < hi_y; y += stepy)
		{
			PointF      pointF(-10, y);
			y = round(y);
			graphics.DrawLine(&pen,-5, y, 5, y);

			char lb[10];
			sprintf_s(lb, "%.2f", y*scaley);

			const WCHAR *string;
			int nChars = MultiByteToWideChar(CP_ACP, 0, lb, -1, NULL, 0);
			// allocate it
			string = new WCHAR[nChars];
			MultiByteToWideChar(CP_ACP, 0, lb, -1, (LPWSTR)string, nChars);
			graphics.DrawString(string, -1, &font, pointF, &solidBrush);
		}

		for (int y = 0; y > lo_y; y -= stepy)
		{
			PointF      pointF(-10, y);
			y = round(y);
			graphics.DrawLine(&pen, -5, y, 5, y);

			char lb[10];
			sprintf_s(lb, "%.2f", y*scaley);

			const WCHAR *string;
			int nChars = MultiByteToWideChar(CP_ACP, 0, lb, -1, NULL, 0);
			// allocate it
			string = new WCHAR[nChars];
			MultiByteToWideChar(CP_ACP, 0, lb, -1, (LPWSTR)string, nChars);
			graphics.DrawString(string, -1, &font, pointF, &solidBrush);
		}
	}

	

	

	//int round(int n)
	//{
	//	if (n < 10) {
	//		return n;
	//	}
	//	int a = (n / 10) * 10;

	//	// Larger multiple 
	//	int b = a + 10;

	//	// Return of closest of two 
	//	return (n - a > b - n) ? b : a;
	//}
};

#endif
