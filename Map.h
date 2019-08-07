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
		MAP1 = 1,
		MAP2,
		MAP3,
		T_MAPCOUNT,
	};
	std::vector<HBITMAP> _maplist;
	HBITMAP _curMap;
	HDC _hdc;
	//������ ���۰� ��(�ʱ��� ���δ� �뵵)
	std::unordered_map<int, std::pair<int, int>> floorRange;
	void SelectMapNum(int numMap);
public:
	
};

