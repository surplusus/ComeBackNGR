#pragma once
#include "InGamePart.h"

class Map : public InGamePart
{
public:
	Map(PartsMgr*);
	virtual ~Map() {}

	virtual void Update() {}
	virtual void Draw() {}
};

