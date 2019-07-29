#pragma once
#include "InGamePart.h"

class Neoguri : public InGamePart
{
public:
	Neoguri(PartsMgr*);
	virtual ~Neoguri() {}

	virtual void Update() {}
	virtual void Draw() {}
};

