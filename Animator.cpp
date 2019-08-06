#include "stdafx.h"
#include "Animator.h"
#include "Basic_Value.h"
#include "Texture.h"

#pragma comment (lib, "msimg32.lib")

Animator::Animator(int idImage, int countImageNum)
{
	_texture = new TextureHandler(idImage, countImageNum);
}

Animator::Animator(std::string nameImage, int countImageNum)
{
	_texture = new TextureHandler(nameImage, countImageNum);
}

void Animator::UpdateAnimeCoord(int x, int y)
{
	_coord.x = x;
	_coord.y = y;
	if (_coord.x < 0)				_coord.x = 0;
	if (_coord.y < 0)				_coord.y = 0;
	if (_coord.x > WindowWidth) 	_coord.x = WindowWidth;
	if (_coord.y > WindowHeight)	_coord.y = WindowHeight;
}

void Animator::DrawAnime(bool isMoving, int speed)
{
	/*BitBlt(g_hmemdc,_coord.x,_coord.y,AnimeSizeWidth,AnimeSizeHeight,
		_texture->GetHDC(),*/
	
	animatorSpeedStandard -= speed;
	if (isMoving && animatorSpeedStandard <= 0)
	{
		_texture->ChangeToNextBitmap();
		animatorSpeedStandard = 1600;
	}
	
	TransparentBlt(g_hmemdc, _coord.x, _coord.y, AnimeSizeWidth, AnimeSizeHeight,
		_texture->GetHDC(), 0, 0, _texture->GetSize().x, _texture->GetSize().y, RGB(0, 0, 0));

}

void Animator::SetAnimeSize(int cx, int cy)
{
	_texture->SetSize(cx, cy);
}
