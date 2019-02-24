#include <iostream>
#include <Windows.h>

int main()
{
	POINT p;
	HWND hWnd = GetConsoleWindow();
	HDC hdc = GetDC(hWnd);
	SelectObject(hdc, GetStockObject(WHITE_PEN));

	MoveToEx(hdc, 50, 50, &p);
	LineTo(hdc, 100, 200);

	//ReleaseDC(hWnd, hdc);

	system("pause");
	return 0;
}