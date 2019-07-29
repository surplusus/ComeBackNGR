#pragma once
#include "InGamePart.h"

class Prey : public InGamePart
{
public:
	Prey(PartsMgr*);
	virtual ~Prey() {}

	virtual void Update() {}
	virtual void Draw() {}
};

