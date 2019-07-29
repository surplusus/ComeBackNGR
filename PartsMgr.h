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
	// part 마다 만들어야된다
	std::multimap<std::type_index, InGamePart*> _parts;
public:
	// part 마다 만들어야된다
	// part 마다 만들때 this를 주입시킨다
	//void AddPart(InGamePart*);
	//void RemovePart(InGamePart*);
	void Mediate(InGamePart*);// 정의부분 수정요
	void AddMonster();
	void AddObstacle();
	void AddPrey();
	void Init();
};

