/*
 * adapted from:
 * http://www.winprog.org/tutorial/simple_window.html
 */

#include <windows.h>
#include <stdio.h>

const char g_szClassName[] = "helloWindowClass";

/* window message handler */
LRESULT CALLBACK HelloWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_COMMAND:
			if ((HIWORD(wParam) == BN_CLICKED) && (lParam != 0))
				MessageBox(hwnd, "Hello World!", "Alert", MB_OK);
			break;

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	HWND hwnd;
	HWND hwndButton;
	MSG msg;

	/* register window class */
	wc.style = 0;
	wc.lpfnWndProc = HelloWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	/* create window */
	hwnd = CreateWindow(
		g_szClassName,
		"Hello",
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		500,
		400,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hwnd)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	/* create button */
	hwndButton = CreateWindow(
		"BUTTON",
		"Click me!",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		10,
		10,
		100,
		50,
		hwnd,
		NULL,
		hInstance,
		NULL
	);

	/* show window */
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	/* run message loop */
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
