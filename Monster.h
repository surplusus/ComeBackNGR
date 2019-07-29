#pragma once
#include "InGamePart.h"

class Monster : public InGamePart
{
public:
	Monster(PartsMgr*);
	virtual ~Monster() {}

	virtual void Update() {}
	virtual void Draw() {}
};

