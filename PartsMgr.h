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

	void AddMonster();
	void AddObstacle();
	void AddPrey();
public:
	// 각 parts에서 부르는 부분
	void Mediate(InGamePart*);// 정의부분 수정요

	 /*part 마다 만들어야된다
	 part 마다 만들때 this를 주입시킨다*/
	void AddPart(InGamePart*);
	void RemovePart(InGamePart*);
	// Scene이 호출하는 부분
	void Init();
	void Draw(); // 각 부분을 그리라고 돌아가면서 시킴
	void Update();
};

