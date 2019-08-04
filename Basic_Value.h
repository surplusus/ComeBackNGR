#pragma once

const int WindowWidth = 900;
const int WindowHeight = 600;
const int MapMaxWidth = 740;
const int MapMinWidth = 50;
const int MapMaxHeight = 515;
const int MapMinHeight = 90;
const int WinStPosX = 10;
const int WinStPosY = 10;
const int AnimeSizeWidth = 42;
const int AnimeSizeHeight = 48;

extern HWND g_hwnd;
extern HDC g_hmemdc;
extern HINSTANCE g_hinst;
extern HBITMAP g_defaultbit;

enum EVENTTYPE
{
	NONE = 0,			// 0000
	DIE = 1,			// 0001
	MONSTER,
	OBSTACLE,
	PRAY,
	AIRTIME,
	LAND,
	LADDER,
};