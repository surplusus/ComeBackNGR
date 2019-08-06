#pragma once
#include "InGamePart.h"
class Animator;

class Prey : public InGamePart
{
public:
	Prey(PartsMgr*,int,int,int);
	virtual ~Prey() {}

	virtual void Update();
	virtual void Draw();
public:
	static std::vector<Prey*> PreyMemberPtr;
private:
	int numOfOrder;
	HBITMAP body;
	Animator* score;
	HDC hdc;
	int isRemoving = 0;
	bool CheckPreysRemain();
	void RemovePreyProcedure();
public:
};

