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
	// part ���� �����ߵȴ�
	std::multimap<std::type_index, InGamePart*> _parts;

	void AddMonster();
	void AddObstacle();
	void AddPrey();
public:
	// �� parts���� �θ��� �κ�(mediator����)
	Map* GetMap();
	Neoguri* GetNeoguri();
	std::vector<Monster*> GetMonsters();
	std::vector<Prey*> GetPreys();
	std::vector<Obstacle*> GetObstacle();

	// Scene�� ȣ���ϴ� �κ�
	void Init();
	void Draw() {} // �� �κ��� �׸���� ���ư��鼭 ��Ŵ
	// �� Ŭ������ Update���� �ڽ��� �׸��� �Լ��� ������
	void Update();
};

