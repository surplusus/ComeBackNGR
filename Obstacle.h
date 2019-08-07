#pragma once
#include "InGamePart.h"

class Obstacle : public InGamePart
{
public:
	Obstacle(PartsMgr*,int,int);
	virtual ~Obstacle() {}

	virtual void Update();
	virtual void Draw();
private:
	HBITMAP _body;
	HDC _hdc;
};

