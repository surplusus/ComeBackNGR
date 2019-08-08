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
	//������ ���۰� ��(�ʱ��� ���δ� �뵵)
	std::unordered_map<int, std::pair<int, int>> floorRange;
	void SelectMapNum(int numMap);

	void ReadJSONConfigFile(int numMap);
	void MakeLadderInMap(const RECT&);
	// EventBus ������ �뵵(Publish)
	void GoToNextMap(EventCheatOperator*);
public:
	// �ʸ���� �Լ�

	//EventBus ȣ�� �Լ�
};

