#include "stdafx.h"
#include "Map.h"

Map::Map(PartsMgr *mgr) : InGamePart(mgr)
{
	maplist.resize(T_MAPCOUNT);

	for (int i = 0; i < T_MAPCOUNT; ++i)
	{
		maplist[i] = LoadBitmap(GetModuleHandle(0), 
			MAKEINTRESOURCE(IDB_BITMAP_MAPSAMPLE + i));
	}
}

void Map::SelectMapNum(int numMap)
{

}
