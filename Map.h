#pragma once
#include "InGamePart.h"
class EventCheatOperator;
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
	HBITMAP _maplist;
	std::unordered_map<std::string,RECT> _outer;
	std::vector<RECT> _ladder;
	std::vector<RECT> _cliff;
	int _curMapNum = 1;
	HDC _hdc;
	//층마다 시작과 끝(너구리 가두는 용도)
	std::unordered_map<int, std::pair<int, int>> floorRange;
	void SelectMapNum(int numMap);

	void ReadJSONConfigFile(int numMap);
	void MakeLadderInMap(const RECT&);
	// EventBus 날리는 용도(Publish)
	void GoToNextMap(EventCheatOperator*);
public:
	// 맵만들기 함수

	//EventBus 호출 함수
};

