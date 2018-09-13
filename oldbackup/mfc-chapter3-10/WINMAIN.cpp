#include "stdafx.h"

LRESULT CALLBACK WindowSunProc(
	HWND,
	UINT,
	WPARAM,
	LPARAM
	);

int WINAPI WinMain(
	HINSTANCE hInstance,      // handle to current instance
	HINSTANCE hPrevInstance,  // handle to previous instance
	LPSTR lpCmdLine,          // command line
	int nCmdShow              // show state
	)
{
	WNDCLASS wndcls;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);
	wndcls.hIcon = LoadIcon(NULL, IDC_CROSS);
	wndcls.hInstance = hInstance;
	wndcls.lpfnWndProc = WindowSunProc;
	wndcls.lpszClassName = "Weixin2003";
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndcls);

	HWND hwnd;
	hwnd = CreateWindow("Weixin2003", "Ich bin Zerd", WS_OVERLAPPEDWINDOW,
		0, 0, 600, 400, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WindowSunProc(
	HWND hwnd,      // handle to window
	UINT uMsg,      // message identifier
	WPARAM wParam,  // first message parameter
	LPARAM lParam   // second message parameter
	)
{
	switch (uMsg)
	{
	case WM_CHAR:
		char szChar[20];
		sprintf_s(szChar, "char is d%", wParam);
		MessageBox(hwnd, szChar, "ff", 0);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, "m  c", "ff", 0);
		HDC hdc;
		hdc = GetDC(hwnd);
		TextOut(hdc, 0, 0, "Zerd", strlen("Zerd"));
		ReleaseDC(hwnd, hdc);
		break;
	case WM_PAINT:
		HDC hDc;
		PAINTSTRUCT ps;
		hDc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	case WM_CLOSE:
		if (IDYES == MessageBox(hwnd, " «∑Ò’ÊΩ· ¯£ø", "ff", MB_YESNO))
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}