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
	std::vector<InGamePart*> _parts;
public:
	// part 마다 만들어야된다
	// part 마다 만들때 this를 주입시킨다
	//void AddPart(InGamePart*);
	//void RemovePart(InGamePart*);
	void Mediate(InGamePart*);// 수정해야될지도
};

