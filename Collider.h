#pragma once
#include <Windows.h>

typedef struct _tagCollider
{
	POINT _pos;
	int _posX;
	int _posY;
	int _cx;
	int _cy;
	RECT _rect;
	_tagCollider(POINT pos1, POINT pos2);
	_tagCollider(int, int, int, int);
	_tagCollider(RECT);
} COLLIDER;

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

inline _tagCollider::_tagCollider(int, int, int, int)
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

inline _tagCollider::_tagCollider(RECT)
{
	_rect = re;
	_posX = re.left;
	_posY = re.top;
	_cx = re.right;
	_cy = re.bottom;
}