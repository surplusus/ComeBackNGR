#pragma once
#include "InGamePart.h"

class Obstacle : public InGamePart
{
public:
	Obstacle(PartsMgr*);
	virtual ~Obstacle() {}

	virtual void Update() {}
	virtual void Draw() {}
};

