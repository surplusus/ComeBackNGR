#include "stdafx.h"
#include "Collider.h"

void Collider::UpdateCollider(POINT checkpos)
{
	int changedRateX = checkpos.x - col._checkPos.x;
	int changedRateY = checkpos.y - col._checkPos.y;
	
	col._posX			+= changedRateX;
	col._posY			+= changedRateY;
	col._cx				+= changedRateX;
	col._cy				+= changedRateY;
	col._checkPos			= checkpos;
	col._rect.left		+= changedRateX;
	col._rect.top		+= changedRateY;
	col._rect.right		+= changedRateX;
	col._rect.bottom	+= changedRateY;
}

void Collider::UpdateCollider(int x1, int y1, int x2, int y2)
{
	col._posX		= x1;
	col._posY		= y1;
	col._cx			= x2;
	col._cy			= y2;
	col._checkPos.x = (x1 + x2) / 2;
	col._checkPos.y = y2;
	col._rect.left   =	x1;
	col._rect.top	 =	y1;
	col._rect.right  =	x2;
	col._rect.bottom =	y2;
}

void Collider::UpdateCollider(RECT re)
{
	col._rect = re;
	col._posX = re.left;
	col._posY = re.top;
	col._cx   = re.right;
	col._cy   = re.bottom;
	col._checkPos.x = (re.left + re.right) / 2;
	col._checkPos.y = re.bottom;
}

bool Collider::OnNGRCollisionEnter()
{
	POINT neo = _parts->GetNGRPosition();
	if (col._rect.left <= neo.x && neo.x <= col._rect.right)
		if (col._rect.top <= neo.y && neo.y <= col._rect.bottom)
			return true;

	return false;
	//if (PtInRect(&col._rect, _parts->GetNGRPosition()))
}
