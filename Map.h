#pragma once
#include "InGamePart.h"

class Map : public InGamePart
{
public:
	Map(PartsMgr*);
	virtual ~Map() {}

	virtual void Update() {}
	virtual void Draw() {}
	void SelectMapNum(int numMap);
private:
	enum T_MAP{
		SAMPLE = 0,
		T_MAPCOUNT
	};
	std::vector<HBITMAP> maplist;
	HBITMAP curMap;

public:

};

