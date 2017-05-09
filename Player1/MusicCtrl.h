#pragma once

#include "Player1.h"
#include "Commctrl.h"
#include <mmsystem.h>
#include <stdio.h>

#define MAXBUTTONS 50
#define MAXTRACKBARS 3
#define TRACKBAR_CLASS "msctls_trackbar32"

struct oneButton
{
	HWND hWnd;
	HBITMAP hBmp;
	int left;
	int top;
	int width;
	int height;
	bool showed;
};

struct oneTrack
{
	HWND hWnd;
	int left;
	int top;
	int width;
	int height;
	bool showed; 
	bool horiz;	  // Горизонтальный или нет
	int maxValue; // Максимальная величина 
	int poz;	  // Позиция трекбара (0-maxValue)

};

class MusicCtrl
{
private:
	void AddButton(int i, char *sName, char *sIconName, int left, int top, int width, int height, int show);
	void AddButton(int i);

	void AddTrackBar(int i, char *sName, char *sType, int left, int top, int width, int height, int show, int maxValue, int poz);
	void AddTrackBar(int i);

	void HideButton(int i);
	void ShowButton(int i);
	void SetTrackpos(int v);
	void SetMusTrac(int m);

public:
	static enum WINDOWS { wPlay = 0, wEnd, wNext, wPrev, wRepeat, wLike, wNoLike, wMix, wPause, wFullVolume, wMid_volume, wLow_volume, wOff_volume, wNoMix, wNoRepeat };
	static int nButtons;
	char sPath[256];
	char sIniPath[256];
	char sFullPath[256];

	HWND hWnd;
	HINSTANCE hInst;

	//HWND tracks[0].hWnd;
	//HWND hTrackWnd;

	//int pozTrack;
	int isPlay;
	int isVolume;
	int isLike;
	int isMix;
	int isRepeat;
	bool isOpen;
	int iType; // 1-Mp3; 2-Wav

	HBITMAP oldBitmap;
	HANDLE hBitmap;
	char s[100];
	oneButton buttons[MAXBUTTONS];
	oneTrack tracks[MAXTRACKBARS];
	void Init(HWND hWnd_, HINSTANCE hInst_);
	void DoCmd(HWND hBtnWnd);
	bool OpenFile();
	void SetVolume();


	MusicCtrl();
	~MusicCtrl();
};

