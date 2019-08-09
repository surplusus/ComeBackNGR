#include "stdafx.h"
#include "Basic_Value.h"

HWND g_hwnd = nullptr;
HDC g_hmemdc = nullptr;
HINSTANCE g_hinst = nullptr;
HBITMAP g_defaultbit = LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP_DEFAULTBG));