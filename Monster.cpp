#include "stdafx.h"
#include "Monster.h"
#include "Basic_Value.h"

Monster::Monster(PartsMgr *mgr, POINT p, int startDir) 
	: InGamePart(mgr), _pos(p)
{
	_collider.left = _pos.x;
	_collider.bottom = _pos.y;
	_collider.top = _pos.y + 40;
	_collider.right = _pos.x + 20;

	state = static_cast<STATE>(startDir);
}

void Monster::Update()
{
	POINT posNGR = InGamePart::_partsManager->GetNGRPosition();
	if (PtInRect(&_collider, posNGR))
		OnNotify(EVENTTYPE::DIE);
}

void Monster::SetPatrolCoordinate(int startX, int endX)
{
	_startPatrolX = startX;
	_endPatrolX = endX;
}
