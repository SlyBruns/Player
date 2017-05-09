#include "stdafx.h"

#include <Commdlg.h>

#include "MusicCtrl.h"

int MusicCtrl::nButtons = 0;

MusicCtrl::MusicCtrl()
{
	GetCurrentDirectory(256, sPath);
	sprintf(sIniPath, "%s\\Buttons.txt", sPath);

}


MusicCtrl::~MusicCtrl()
{
	// Освобождать битмэпы

	for (int i = 0; i < nButtons; i++)
		DeleteObject(buttons[i].hBmp);

	// Удалять окна
	for (int i = 0; i < nButtons; i++)
		DestroyWindow(buttons[i].hWnd);

}

void MusicCtrl::Init(HWND hWnd_, HINSTANCE hInst_)
{
	hWnd = hWnd_;
	hInst = hInst_;
	
	isPlay = 0;
	isVolume = 0;
	isLike = 0;
	isMix = 0;
	isRepeat = 0;
	isOpen = false;

	AddButton(wPlay);
	AddButton(wEnd);
	AddButton(wNext);
	AddButton(wPrev);
	AddButton(wRepeat);
	AddButton(wLike);
	AddButton(wNoLike);
	AddButton(wMix);
	AddButton(wPause);
	AddButton(wFullVolume);
	AddButton(wMid_volume);
	AddButton(wLow_volume);
	AddButton(wOff_volume);
	AddButton(wNoMix);
	AddButton(wNoRepeat);

	//Звуковая дорожка.
	AddTrackBar(0);
	AddTrackBar(1);

	iType = 0;

	//tracks[0].hWnd = CreateWindow(TRACKBAR_CLASS, "TrackBar Demo",
	//	WS_CHILD | WS_VISIBLE | WS_TABSTOP | TBS_AUTOTICKS,
	//	100, 300, 300, 33, hWnd, NULL, hInst, NULL);
	//SendMessage(tracks[0].hWnd, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
	//pozTrack = 100;
	//SendMessage(tracks[0].hWnd, TBM_SETPOS, TRUE, pozTrack);

	MoveWindow(hWnd, 100, 100, 500, 400, true);


}
void MusicCtrl::HideButton(int i)
{
	ShowWindow(buttons[i].hWnd, SW_HIDE);
}

void MusicCtrl::ShowButton(int i)
{
	ShowWindow(buttons[i].hWnd, SW_SHOW);
}

void MusicCtrl::AddTrackBar(int i, char *sName, char *sType, int left, int top, int width, int height, int show, int maxValue, int poz)
{
	if (strcmp(sType, "HORIZ_TRACKBAR") == 0)
	{
		tracks[i].hWnd = CreateWindow(TRACKBAR_CLASS, sName,
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | TBS_AUTOTICKS | TBS_HORZ,
			left, top, width, height, hWnd, NULL, hInst, NULL);
		tracks[i].horiz = true;

		tracks[i].maxValue = maxValue;
		SendMessage(tracks[i].hWnd, TBM_SETRANGE, TRUE, MAKELONG(0, maxValue));
	}
	else 
	if (strcmp(sType, "VERT_TRACKBAR") == 0)
	{
		tracks[i].hWnd = CreateWindow(TRACKBAR_CLASS, sName,
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | TBS_AUTOTICKS | TBS_VERT,
			left, top, width, height, hWnd, NULL, hInst, NULL);
		tracks[i].horiz = false;

		tracks[i].maxValue = maxValue;
		SendMessage(tracks[i].hWnd, TBM_SETRANGE, TRUE, MAKELONG(0, maxValue));

	}
	else
		return;
	
	if (tracks[i].horiz)
		tracks[i].poz = poz;
	else
		tracks[i].poz = tracks[i].maxValue - poz;

	SendMessage(tracks[0].hWnd, TBM_SETPOS, TRUE, poz);

	tracks[i].left = left;
	tracks[i].top = top;
	tracks[i].width = width;
	tracks[i].height = height;
	tracks[i].showed = (bool)show;
	if (!tracks[i].showed)
		ShowWindow(tracks[i].hWnd, SW_HIDE);
}

void MusicCtrl::AddButton(int i, char *sName, char *sIconName, int left, int top, int width, int height, int show)
{
	buttons[i].hWnd = CreateWindow("BUTTON", sName,
		WS_CHILD | WS_VISIBLE | BS_BITMAP,
		left, top, width, height, hWnd, NULL, hInst, NULL);
	buttons[i].hBmp = (HBITMAP)LoadImage(NULL, sIconName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (buttons[i].hBmp)
		SendMessage(buttons[i].hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)buttons[i].hBmp);
	buttons[i].left = left;
	buttons[i].top = top;
	buttons[i].width = width;
	buttons[i].height = height;
	buttons[i].showed = (bool)show;
	if (!buttons[i].showed)
		HideButton(i);
	nButtons++;
}

void MusicCtrl::SetTrackpos(int v)
{
	SendMessage(tracks[0].hWnd, TBM_SETPOS, TRUE, v);
	tracks[0].poz = v;
	InvalidateRect(hWnd, NULL, true);
}

void MusicCtrl::SetMusTrac(int m)
{

}
// https://technet.microsoft.com/en-us/bb760147

void MusicCtrl::AddTrackBar(int i)
{
	char sName[32];
	char sType[256];
	char sSection[32];
	sprintf(sSection, "TRACKBAR%d", i + 1);
	GetPrivateProfileString(sSection, "name", NULL, sName, 32, sIniPath);
	GetPrivateProfileString(sSection, "type", NULL, sType, 256, sIniPath);
	int left = GetPrivateProfileInt(sSection, "left", 0, sIniPath);
	int top = GetPrivateProfileInt(sSection, "top", 0, sIniPath);
	int width = GetPrivateProfileInt(sSection, "width", 0, sIniPath);
	int height = GetPrivateProfileInt(sSection, "height", 0, sIniPath);
	int show = GetPrivateProfileInt(sSection, "show", 0, sIniPath);
	int maxValue = GetPrivateProfileInt(sSection, "max", 100, sIniPath);
	int poz = GetPrivateProfileInt(sSection, "poz", 100, sIniPath);
	
	AddTrackBar(i, sName, sType, left, top, width, height, show, maxValue, poz);

}
void MusicCtrl::AddButton(int i)
{
	char sName[32];
	char sIconName[256];
	char sSection[32];
	sprintf(sSection, "BUTTON%d", i + 1);
	GetPrivateProfileString(sSection, "name", NULL, sName, 32, sIniPath);
	GetPrivateProfileString(sSection, "iconname", NULL, sIconName, 256, sIniPath);
	int left = GetPrivateProfileInt(sSection, "left", 0, sIniPath);
	int top = GetPrivateProfileInt(sSection, "top", 0, sIniPath);
	int width = GetPrivateProfileInt(sSection, "width", 0, sIniPath);
	int height = GetPrivateProfileInt(sSection, "height", 0, sIniPath);
	int show = GetPrivateProfileInt(sSection, "show", 0, sIniPath);
	AddButton(i, sName, sIconName, left, top, width, height, show);
}
void MusicCtrl::DoCmd(HWND hBtnWnd)
{
	// Избранная аудио запись
	if (hBtnWnd == buttons[wLike].hWnd)
	{
		HideButton(wLike);
		ShowButton(wNoLike);
		isLike = 1;
	}
	else 
	if (hBtnWnd == buttons[wNoLike].hWnd)
	{
		HideButton(wNoLike);
		ShowButton(wLike);
		isLike = 0;
	}
	// Повторение трека
	else
	if (hBtnWnd == buttons[wRepeat].hWnd)
	{
		HideButton(wRepeat);
		ShowButton(wNoRepeat);
		isMix = 1;
	}
	else
	if (hBtnWnd == buttons[wNoRepeat].hWnd)
	{
		HideButton(wNoRepeat);
		ShowButton(wRepeat);
		isMix = 0;
	}
	// Микс треков
	else
	if (hBtnWnd == buttons[wMix].hWnd)
	{
		HideButton(wMix);
		ShowButton(wNoMix);
		isMix = 1;
	}
	else
	if (hBtnWnd == buttons[wNoMix].hWnd)
	{
		HideButton(wNoMix);
		ShowButton(wMix);
		isMix = 0;
	}
	// выводить значение трекбара
	else
	if (hBtnWnd == buttons[wFullVolume].hWnd)
	{
		HideButton(wFullVolume);
		ShowButton(wMid_volume);
		isVolume = 1;
		SetTrackpos(50);
		SetVolume();
	}
	else
	if (hBtnWnd == buttons[wMid_volume].hWnd)
	{
		HideButton(wMid_volume);
		ShowButton(wLow_volume);
		isVolume = 2;
		SetTrackpos(20);
		SetVolume();
	}
	else
	if (hBtnWnd == buttons[wLow_volume].hWnd)
	{
		HideButton(wLow_volume);
		ShowButton(wOff_volume);
		isVolume = 3;
		SetTrackpos(0);
		SetVolume();
	}
	else
	if (hBtnWnd == buttons[wOff_volume].hWnd)
	{
		HideButton(wOff_volume);
		ShowButton(wFullVolume);
		isVolume = 0;
		SetTrackpos(100);
		SetVolume();
	}
	else
	if (hBtnWnd == buttons[wPlay].hWnd)
	{

		if (isPlay == 0)
		{
			//mciSendString("open D:\\temp\\music\\test.mp3 alias MP3", NULL, 0, NULL); 
			HideButton(wPlay);
			ShowButton(wPause);
			mciSendString("play MP3", NULL, 0, NULL);
			isPlay = 1;
		}
		else
		if (isPlay == 2)

		{
			HideButton(wPlay);
			ShowButton(wPause);
			mciSendString("resume MP3", NULL, 0, NULL);
			isPlay = 1;
		}
	}
	else
	if (hBtnWnd == buttons[wPause].hWnd)
	{

		if (isPlay == 1)
		{
			HideButton(wPause);
			ShowButton(wPlay);
			mciSendString("pause MP3", NULL, 0, NULL);
			isPlay = 2;
		}
	}
	else
	if (hBtnWnd == buttons[wEnd].hWnd)
	{
		char mciStr[MAX_PATH] = { 0 };
		//HideButton(wEnd);
		HideButton(wPause);
		ShowButton(wPlay);
		mciSendString("close MP3", NULL, 0, NULL);
		isPlay = 0;
	}
	else
	if (hBtnWnd == tracks[0].hWnd)
	{
		tracks[0].poz = SendMessage(tracks[0].hWnd, TBM_GETPOS, 0, 0);
		InvalidateRect(hWnd, NULL, true);
		SetVolume();
	}


}
bool MusicCtrl::OpenFile()
{
				/////////////////////////////////////////////////////////////////////
				OPENFILENAME ofn;       // common dialog box structure
				char szFile[260] = { 0 };       // buffer for file name

				// Initialize OPENFILENAME
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = hWnd;
				ofn.lpstrFile = szFile;
				// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
				// use the contents of szFile to initialize itself.
				ofn.lpstrFile[0] = '\0';
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = "All\0*.*\0MP3\0*.MP3";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;

				// Display the Open dialog box. 

				isOpen = false;
				if (!(GetOpenFileName(&ofn) == TRUE)) return false;
				/////////////////////////////////////////////////////////////////////

				SetWindowText(hWnd, ofn.lpstrFile);
				
				int ls = strlen(ofn.lpstrFile);
				if (stricmp(".MP3", ofn.lpstrFile + ls - 4) == 0)
					iType = 1;
				else
				if (stricmp(".WAV", ofn.lpstrFile + ls - 4) == 0)
					iType = 2;
				else
				if (stricmp(".MVA", ofn.lpstrFile + ls - 4) == 0)
					iType = 3;
				else
					iType = 0;

				
				char s[256];
				sprintf(s, "open %s alias MP3", ofn.lpstrFile); /// Изменить в зависимости от iType
				
				mciSendString(s, NULL, 0, NULL);

		
				isOpen = true;
				InvalidateRect(hWnd, NULL, TRUE);


				strcpy(sFullPath, ofn.lpstrFile);
				return true;

}
void MusicCtrl::SetVolume()
{
	char sizeVol[260] = { 0 };
	if (tracks[0].poz > 100)
		tracks[0].poz = 100;
	if (tracks[0].poz <= 0)
		tracks[0].poz = 0;
	sprintf(sizeVol, "SetAudio MP3 volume to %d", tracks[0].maxValue - tracks[0].poz);
		mciSendString(sizeVol, NULL, 0, NULL);

}