#include "stdafx.h"
#include "Map.h"
#include "Basic_Value.h"

Map::Map(PartsMgr *mgr) : InGamePart(mgr)
{
	_maplist.resize(T_MAPCOUNT);

	for (int i = 0; i < T_MAPCOUNT; ++i)
	{
		_maplist[i] = LoadBitmap(GetModuleHandle(0), 
			MAKEINTRESOURCE(IDB_BITMAP_MAPSAMPLE + i));
	}
	_curMap = _maplist[0];
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
