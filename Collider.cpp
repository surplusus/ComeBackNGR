#include "stdafx.h"
#include "Collider.h"

void Collider::UpdateCollider(POINT checkpos)
{
	int changedRateX = checkpos.x - col._checkPos.x;
	int changedRateY = checkpos.y - col._checkPos.y;
	
	col._posX += changedRateX;
	col._posY += changedRateY;
	col._cx += changedRateX;
	col._cy += changedRateY;
	col._checkPos = checkpos;
	col._rect.left += changedRateX;
	col._rect.top += changedRateY;
	col._rect.right += changedRateX;
	col._rect.bottom += changedRateY;
}

void Collider::UpdateCollider(POINT pos1, POINT pos2)
{
	col._posX = pos1.x;
	col._posY = pos1.y;
	col._cx = pos2.x;
	col._cy = pos2.y;
	col._checkPos.x = (pos1.x + pos2.x) / 2;
	col._checkPos.y = (pos1.y + pos2.y) / 2;
	col._rect.left =	col._posX;
	col._rect.top =		col._posY;
	col._rect.right =	col._cx;
	col._rect.bottom =	col._cy;
}

void Collider::UpdateCollider(int x1, int y1, int x2, int y2)
{
	col._posX = x1;
	col._posY = y1;
	col._cx = x2;
	col._cy = y2;
	col._checkPos.x = (x1 + x2) / 2;
	col._checkPos.y = (y1 + y2) / 2;
	col._rect.left =	col._posX;
	col._rect.top =		col._posY;
	col._rect.right =	col._cx;
	col._rect.bottom =	col._cy;
}

void Collider::UpdateCollider(RECT re)
{
	col._rect = re;
	col._posX = re.left;
	col._posY = re.top;
	col._cx = re.right;
	col._cy = re.bottom;
	col._checkPos.x = (re.left + re.right) / 2;
	col._checkPos.y = (re.top + re.bottom) / 2;
}

bool Collider::OnNGRCollisionEnter()
{
	if (PtInRect(&col._rect, _parts->GetNGRPosition()))
		return true;
	else
		return false;
}
