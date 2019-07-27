#include "stdafx.h"
#include "Texture.h"

_tagTexture::_tagTexture(POINT pos1, POINT pos2)
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

_tagTexture::_tagTexture(int x1, int y1, int x2, int y2)
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

_tagTexture::_tagTexture(RECT re)
{
	_rect = re;
	_posX = re.left;
	_posY = re.top;
	_cx = re.right;
	_cy = re.bottom;
}

void _tagTexture::MakeTexture(int idImage, int numSize)
{
	for (size_t i = 0; i < numSize; i++)
	{
		_images.push_back(LoadBitmap(g_hinst, MAKEINTRESOURCE(idImage + i)));
	}
	HBITMAP a;
}
