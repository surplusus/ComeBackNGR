#include "stdafx.h"
#include "Collider.h"

/////////////STRUCTURE////////////////
_tagCollider::_tagCollider(POINT pos1, POINT pos2)
{
	_pos = pos1;
	_posX = pos1.x;
	_posY = pos1.y;
	_cx = pos2.x;
	_cy = pos2.y;
	_rect.left = _posX;
	_rect.top = _posY;
	_rect.right = _cx;
	_rect.bottom = _cy;
}

_tagCollider::_tagCollider(int x1, int y1, int x2, int y2)
{
	_posX = x1;
	_posY = y1;
	_cx = x2;
	_cy = y2;
	_pos.x = x1;
	_pos.y = y1;
	_rect.left = _posX;
	_rect.top = _posY;
	_rect.right = _cx;
	_rect.bottom = _cy;
}

_tagCollider::_tagCollider(RECT re)
{
	_rect = re;
	_posX = re.left;
	_posY = re.top;
	_cx = re.right;
	_cy = re.bottom;
}


//////////////////Collider/////////////////


Collider::Collider()
{
}


Collider::~Collider()
{
}
