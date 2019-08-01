#pragma once
class InGame;
class InGamePart;
class Map;
class Monster;
class Prey;
class Obstacle;
class Neoguri;

// mediator
class PartsMgr
{
public:
	PartsMgr(InGame*);
	virtual ~PartsMgr();
private:
	InGame* _callerAsScene;
	// part 마다 만들어야되지만
	// InGamePart에 각각 타입을 key로 값는 멀티맵을 써보았다
	std::multimap<std::type_index, InGamePart*> _parts;

	void AddMonster();
	void AddObstacle();
	void AddPrey();
public:
	// 각 parts에서 부르는 부분(mediator역할)
	Map* GetMap();
	Neoguri* GetNeoguri();
	std::vector<Monster*> GetMonsters();
	std::vector<Prey*> GetPreys();
	std::vector<Obstacle*> GetObstacle();

	// Scene이 호출하는 부분
	void Init();
	void Draw(); // 각 부분을 그리라고 돌아가면서 시킴
	// 각 클래스가 Update이후 자신을 그리는 함수를 실행함
	void Update();
};

