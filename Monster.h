#pragma once
#include "InGamePart.h"

class Monster : public InGamePart
{
private:
	enum STATE{M_LEFT=0,M_RIGHT};
public:
	Monster(PartsMgr*, POINT, int);
	virtual ~Monster() {}

	virtual void Update();
	virtual void Draw() {}
private:
	POINT _pos;
	RECT _collider;
	STATE state;
	int _startPatrolX;
	int _endPatrolX;
public:
	// partMgr이 만들때 정한다.
	void SetPatrolCoordinate(int startX, int endX);
};

