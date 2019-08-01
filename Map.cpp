#include "stdafx.h"
#include "Map.h"

Map::Map(PartsMgr *mgr) : InGamePart(mgr)
{
	_maplist.resize(T_MAPCOUNT);

	for (int i = 0; i < T_MAPCOUNT; ++i)
	{
		_maplist[i] = LoadBitmap(GetModuleHandle(0), 
			MAKEINTRESOURCE(IDB_BITMAP_MAPSAMPLE + i));
	}
	_curMap = _maplist[0];
}

void Map::Update()
{
	static int numMap = 0;
	if (false) //�������� ���̸� �ٸ����� 
		SelectMapNum(++numMap);
}


void Map::SelectMapNum(int numMap)
{
	_curMap = _maplist[numMap];
}
