#pragma once
#include "InGamePart.h"
class CheatOperator;
class EventBus;

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
	int _curMapNum = 1;
	HDC _hdc;
	// EventBus 용
	EventBus* eventbus;
	CheatOperator* cheat;
	//층마다 시작과 끝(너구리 가두는 용도)
	std::unordered_map<int, std::pair<int, int>> floorRange;
	void SelectMapNum(int numMap);
public:
	void GoToNextMap(CheatOperator*);


};

