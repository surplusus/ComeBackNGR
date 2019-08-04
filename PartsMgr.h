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
	// part 마다 만들어야되지만
	// InGamePart에 각각 타입을 key로 값는 멀티맵을 써보았다
	std::unordered_map<std::string, InGamePart*> _parts;
	// 너구리의 현재좌표(필요없을듯)
	POINT _posNGR;
	// mon, ob, prey 갯수
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
	// 각 parts에서 부르는 부분(mediator역할)
	Map* GetMap();
	Neoguri* GetNeoguri();
	std::vector<Monster*> GetMonsters();
	std::vector<Prey*> GetPreys();
	std::vector<Obstacle*> GetObstacle();
	const POINT GetNGRPosition() const { return _posNGR; }
	inline void SetNGRPosition(const POINT p) { _posNGR = p; }
	// Scene이 호출하는 부분
	void Init();
	void Update();	// 돌아가면서 Update
	void Draw();	// 각 부분을 Draw 차례를 설정
	// 이벤트를 받았을때
	virtual void ReceiveEvent(Subject* sub, int evt);
};

