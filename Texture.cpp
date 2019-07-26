#include "stdafx.h"
#include "Texture.h"

Texture::Texture(POINT pos1, POINT pos2)
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

Texture::Texture(int x1, int y1, int x2, int y2)
{

}

Texture::Texture(RECT re)
{

}

void Texture::MakeTexture(WCHAR * filename)
{
	_tcprintf_s(_filename, "%s", filename);
	CreateCompatibleBitmap(_hdc, _cx, _cy);

}
