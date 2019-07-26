#pragma once
class Texture
{
	BITMAP _image;
	HBITMAP _bit;
	HBITMAP _oldbit;
	HDC _hdc;
	WCHAR _filename[64];
	POINT _pos;
	int _posX;
	int _posY;
	int _cx;
	int _cy;
	RECT _rect;
	explicit Texture(POINT pos1,POINT pos2);
	explicit Texture(int, int ,int,int);
	explicit Texture(RECT);
	void MakeTexture(WCHAR* filename);
};

