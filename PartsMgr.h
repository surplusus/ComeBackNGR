#pragma once
#pragma region Ŭ���� ����κ�
#include "Collider.h"
class Observer;
class InGame;
class InGamePart;
class Map;
class Monster;
class Prey;
class Obstacle;
class Neoguri;
//Event Class
class EventPreyRemove;
#pragma endregion
// mediator
class PartsMgr : public Observer
{
public:
	PartsMgr(InGame*);
	virtual ~PartsMgr();
private:
	InGame* _callerAsScene;
	// part ���� �����ߵ�����
	// InGamePart�� ���� Ÿ���� key�� ���� ��Ƽ���� �Ẹ�Ҵ�
	// Draw()�� ���ؼ� ��ϵǾ��ִ� key���� vector�� ������ �ִ�
	std::unordered_map<std::string, InGamePart*> _parts;
	std::list<InGamePart*> _partsOrderList;
	bool isDrawOrderDirty = true;
	// �ʱ����� ������ǥ
	POINT _posNGR;
	// mon, ob, prey ����
	int cntMon = 0;
	int cntObs = 0;
	int cntPrey = 0;
	int numOfCurrentMap = 1;

	TimeMgr* timer = TimeMgr::GetInstance();
	
	void AddMonster(int numOfFloorOn, int srtX, int endX, int dir);
	void AddObstacle(int numOfFloorOn, int coordX);
	void AddPrey(int numOfFloorOn, int coordX);
	void AddMap(int num);
	std::string MakePartIndexName(const char name, int num = -1);
	void MakeDrawOrder();
public:
	friend class Collider;
	// �� parts���� �θ��� �κ�(mediator����) �̾�����
	// ������ Draw()���� �θ���
	Neoguri* GetNeoguri();
	/*Map* GetMap();
	std::vector<Monster*> GetMonsters();
	std::vector<Prey*> GetPreys();
	std::vector<Obstacle*> GetObstacle();*/

	const POINT& GetNGRPosition() const { return _posNGR; }
	inline void SetNGRPosition(const POINT& p) {
		_posNGR.x = p.x;	_posNGR.y = p.y + 10;
	}
	// Scene�� ȣ���ϴ� �κ�
	void Init();
	void Update();	// ���ư��鼭 Update
	void Draw();	// �� �κ��� Draw ���ʸ� ����
	// �̺�Ʈ�� �޾�����
	virtual void OnNotifyEvent(Subject* sub, int evt);
	void RemovePrey(EventPreyRemove* evnt);
};

