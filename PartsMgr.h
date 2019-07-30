#pragma once
class InGame;
class InGamePart;
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
	// �� parts���� �θ��� �κ�
	void Mediate(InGamePart*);// ���Ǻκ� ������

	 /*part ���� �����ߵȴ�
	 part ���� ���鶧 this�� ���Խ�Ų��*/
	void AddPart(InGamePart*);
	void RemovePart(InGamePart*);
	// Scene�� ȣ���ϴ� �κ�
	void Init();
	void Draw(); // �� �κ��� �׸���� ���ư��鼭 ��Ŵ
	void Update();
};

