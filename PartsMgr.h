#pragma once
#include "Collider.h"
#include "ChainResponsibility.h"
class Observer;
class Chain;
class InGame;
class InGamePart;
class Map;
class Monster;
class Prey;
class Obstacle;
class Neoguri;

// mediator
class PartsMgr : public Observer, public Chain
{
public:
	PartsMgr(InGame*);
	virtual ~PartsMgr();
private:
	InGame* _callerAsScene;
	// part ���� �����ߵ�����
	// InGamePart�� ���� Ÿ���� key�� ���� ��Ƽ���� �Ẹ�Ҵ�
	std::unordered_map<std::string, InGamePart*> _parts;
	// �ʱ����� ������ǥ(�ʿ������)
	POINT _posNGR;
	// mon, ob, prey ����
	int cntMon = 0;
	int cntObs = 0;
	int cntPrey = 0;

	void AddMonster(int x, int y, int srtX, int endX, int dir);
	void AddObstacle();
	void AddPrey();
	std::string MakeMapIndexName(const char name, int num = -1);
	void MakeChain();
public:
	//
	friend class Collider;
	// �� parts���� �θ��� �κ�(mediator����)
	Map* GetMap();
	Neoguri* GetNeoguri();
	std::vector<Monster*> GetMonsters();
	std::vector<Prey*> GetPreys();
	std::vector<Obstacle*> GetObstacle();
	const POINT GetNGRPosition() const { return _posNGR; }
	inline void SetNGRPosition(const POINT p) { _posNGR = p; }
	// Scene�� ȣ���ϴ� �κ�
	void Init();
	void Update();	// ���ư��鼭 Update
	void Draw();	// �� �κ��� Draw ���ʸ� ����
	// �̺�Ʈ�� �޾�����
	virtual void ReceiveEvent(Subject* sub, int evt);
};

