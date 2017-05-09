#include "stdafx.h"
#include "Player1.h"
#include "Commctrl.h"
#include <mmsystem.h>
#include <stdio.h>

#include "MusicCtrl.h"

#define MAX_LOADSTRING 100


// Global Variables:
extern HINSTANCE hInst;								// current instance
extern TCHAR szTitle[MAX_LOADSTRING];				// The title bar text
extern TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
extern ATOM				MyRegisterClass(HINSTANCE hInstance);
extern BOOL				InitInstance(HINSTANCE, int);
extern LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
extern INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

extern HWND hWnd;

MusicCtrl musicCtrl;

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static char s[100];
	RECT rect;

	switch (message)
	{
	case WM_CREATE:

		musicCtrl.Init(hWnd, hInst);

		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_OPEN:
			musicCtrl.OpenFile();

				break;

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		case BN_CLICKED:

			musicCtrl.DoCmd((HWND)lParam);

			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		break;

	case WM_PAINT:
	{
		 hdc = BeginPaint(hWnd, &ps);			
		 sprintf(s, "%d", musicCtrl.tracks[0].maxValue - musicCtrl.tracks[0].poz);
		 TextOut(hdc, 410, 300, s, strlen(s));
		 EndPaint(hWnd, &ps);
		
	}
		break;

	case WM_HSCROLL:
		musicCtrl.DoCmd((HWND)lParam);
		break;

	case WM_VSCROLL:
		musicCtrl.DoCmd((HWND)lParam);
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
