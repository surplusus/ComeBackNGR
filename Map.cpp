#include "stdafx.h"
#include "Map.h"
#include "Basic_Value.h"
#include "EventBus.h"
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
	_hdc = CreateCompatibleDC(g_hmemdc);

	// EventBus 실험 
	eventbus->Subscribe(this, &Map::GoToNextMap);
}

void Map::Update()
{
	
}

void Map::Draw()
{
	if (_maplist[_curMapNum] == NULL)
	{
		std::cout << "맵 HBITMAP이 NULL 입니다." << std::endl;
		exit(0);
	}
	SelectObject(_hdc, _maplist[_curMapNum]);
	BitBlt(g_hmemdc, 0, 0, WindowWidth, WindowHeight, _hdc, 0, 0, SRCCOPY);
#ifdef _DEBUG
	static bool flag = false;
	if (!flag)	{
		std::cout << "맵 그리기" << std::endl;
		flag = true;
	}
#endif // _DEBUG
}

void Map::SelectMapNum(int num)
{
	_curMapNum = num;
}

void Map::GoToNextMap(CheatOperator* cheat)
{
	std::cout << "eventbus 실험중" << std::endl;
	cheat->_map->_maplist[++_curMapNum];
}
