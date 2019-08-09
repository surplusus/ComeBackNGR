#pragma once
#include "InGamePart.h"
class Animator;

class Prey : public InGamePart
{
public:
	Prey(PartsMgr*, std::string, int,int,int);
	virtual ~Prey() {}

	virtual void Update();
	virtual void Draw();
public:
	static std::vector<Prey*> PreyMemberPtr;
private:
	std::string name;
	int numOfOrder;
	int numOfRemainedPrey;
	bool isRemoving = false;
	HBITMAP body;
	Animator* score;
	HDC hdc;
	bool CheckPreysRemain();
public:
	bool RemovePreyProcedure();
	std::string GetName() { return name; }
};
