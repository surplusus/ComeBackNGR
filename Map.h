#pragma once
#include "InGamePart.h"

class Map : public InGamePart
{
public:
	Map(PartsMgr*);
	virtual ~Map() {}

	virtual void Update();
	virtual void Draw();
private:
	enum T_MAP{
		SAMPLE = 0,
		T_MAPCOUNT
	};
	std::vector<HBITMAP> _maplist;
	HBITMAP _curMap;
	HDC _hdc;
	void SelectMapNum(int numMap);
public:
	
};

