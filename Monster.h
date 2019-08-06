#pragma once
#include "InGamePart.h"
class PartsMgr;
class Animator;
class Monster : public InGamePart
{
public:
	Monster(PartsMgr*, int, int, int, int);
	virtual ~Monster() {}
	
	virtual void Update();
	virtual void Draw();
private:
	int movingSpeed;
	int _startPatrolX;
	int _endPatrolX;
	std::unordered_map<std::string, Animator*> body;
	Animator* _curBody;
};

