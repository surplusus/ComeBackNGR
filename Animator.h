#pragma once
#include "Texture.h"
#include "Basic_Value.h"

class Animator
{
public:
	Animator() {}
	~Animator() {}
private:
	TextureHandler* _texture = nullptr;
	POINT _coord = { 0,0 };

public:
	enum {NEOGURI,MONSTER, OPENING,ENDING	};

	void UpdateAnimeCoord(int, int);
	void MakeTexture(int idImage, int countImageNum);
	HBITMAP GetAnimeHBITMAP() { return _texture->_texture._bit; }

};

void Animator::UpdateAnimeCoord(int x, int y)
{
	_coord.x += x;
	_coord.y += y;
	if (_coord.x < 0)				_coord.x = 0;
	if (_coord.y < 0)				_coord.y = 0;
	if (_coord.x > WindowWidth) 	_coord.x = WindowWidth;
	if (_coord.y > WindowHeight)	_coord.y = WindowHeight;
}

inline void Animator::MakeTexture(int idImage, int countImageNum)
{
	_texture = new TextureHandler(idImage, countImageNum);
}
