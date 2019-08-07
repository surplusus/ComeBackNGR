#include "stdafx.h"
#include "Map.h"
#include "Basic_Value.h"
using std::string;
using std::stringstream;

Map::Map(PartsMgr *mgr) : InGamePart(mgr)
{
	_maplist.resize(T_MAPCOUNT);
	stringstream ss;
	for (int i = 1; i < T_MAPCOUNT; ++i)
	{
		ss << "image/map/map" << i << ".bmp";
		std::cout << ss.str() << std::endl;
		string st3 = ss.str();
		//_maplist[i] = LoadBitmap(GetModuleHandle(0), 
		//	MAKEINTRESOURCE(IDB_BITMAP_MAPSAMPLE + i));
		size_t origsize = st3.length() + 1;
		size_t convertedChars = 0;
		wchar_t wcstring[30];
		mbstowcs_s(&convertedChars, wcstring, origsize, st3.c_str(), _TRUNCATE);
		_maplist[i-1] = (HBITMAP)LoadImage(NULL,wcstring,IMAGE_BITMAP
			,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		ss.str("");
	}
	_curMap = _maplist[1];
	_hdc = CreateCompatibleDC(g_hmemdc);
}

void Map::Update()
{
	static int numMap = 0;
	if (false) //¿ÉÀú¹ö·Î ¸ÔÀÌ¸¦ ´Ù¸ÔÀ¸¸é 
		SelectMapNum(++numMap);
}

void Map::Draw()
{
	if (_curMap == NULL)
	{
		std::cout << "¸Ê HBITMAPÀÌ NULL ÀÔ´Ï´Ù." << std::endl;
		exit(0);
	}
	SelectObject(_hdc, _curMap);
	BitBlt(g_hmemdc, 0, 0, WindowWidth, WindowHeight, _hdc, 0, 0, SRCCOPY);
#ifdef _DEBUG
	static bool flag = false;
	if (!flag)	{
		std::cout << "¸Ê ±×¸®±â" << std::endl;
		flag = true;
	}
#endif // _DEBUG

}

void Map::SelectMapNum(int numMap)
{
	_curMap = _maplist[numMap];
}
