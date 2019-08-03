#pragma once
#include "Observer.h"
#include "ChainResponsibility.h"
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
	std::map<std::string, InGamePart*> _parts;
	// �ʱ����� ������ǥ
	POINT _posNGR;

	void AddMonster(int x, int y, int srtX, int endX, int dir);
	void AddObstacle();
	void AddPrey();
public:
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
	void Draw(); // �� �κ��� �׸���� ���ư��鼭 ��Ŵ
	// �� Ŭ������ Update���� �ڽ��� �׸��� �Լ��� ������
	void Update();
	// �̺�Ʈ�� �޾�����
	virtual void ReceiveEvent(Subject* sub, int evt);
	// å�ӿ��⸦ ����� ����(Collider?!?!)
	void 
};

