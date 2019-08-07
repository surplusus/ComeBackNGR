#pragma once

const int WindowWidth = 920;
const int WindowHeight = 620;

const int MapMaxWidth = 740;
const int MapMinWidth = 50;
const int MapMaxHeight = 515;
const int MapMinHeight = 90;

const int WinStPosX = 10;
const int WinStPosY = 10;

const int AnimeSizeWidth = 42;
const int AnimeSizeHeight = 48;

const int FirstFloor = 465;
const int SecondFloor = 375;
const int ThirdFloor = 285;
const int FourthFloor = 195;
const int FifthFloor = 105;

extern HWND g_hwnd;
extern HDC g_hmemdc;
extern HINSTANCE g_hinst;
extern HBITMAP g_defaultbit;

enum EVENTTYPE
{
	NONE = 0,			// 0000 0000
	DIE = 1,			// 0000 0001
	MONSTER = 2,		// 0000 0010
	OBSTACLE = 4,		// 0000 0100
	NOPRAYLEFT = 8,			// 0000 1000
	AIRTIME = 16,		// 0001 0000
	LAND = 32,			// 0010 0000
	LADDER = 64,		// 0100 0000
	NEXTSTAGE = 128		// 1000 0000
};