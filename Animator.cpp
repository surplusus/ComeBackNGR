#include "stdafx.h"
#include "Animator.h"
#include "Basic_Value.h"
#include "Texture.h"

#pragma comment (lib, "msimg32.lib")

Animator::Animator(std::string name, int idImage, int countImageNum)
{
	timeName = name;
	_texture = new TextureHandler(idImage, countImageNum);
	timer->SetPeriod(name);
	deltaTime = timer->DeltaTime(name);
}

Animator::Animator(std::string name, std::string nameImage, int countImageNum)
{
	timeName = name;
	_texture = new TextureHandler(nameImage, countImageNum);
	timer->SetPeriod(name);
	deltaTime = timer->DeltaTime(name);
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

const bool Animator::IsOneTickOver() const
{
	return (_texture->GetNumTextureImageCount() - _texture->GetNumOfCurrentTextureImage() == 1);
}

void Animator::DrawAnime(bool isMoving, int speed)
{
	if (isMoving)
	{
		if (timer->DeltaTime(timeName) - deltaTime >= speed)
		{
			_texture->ChangeToNextBitmap();
			deltaTime = timer->DeltaTime(timeName);
		}
	}
	
	TransparentBlt(g_hmemdc, _coord.x, _coord.y, AnimeSizeWidth, AnimeSizeHeight,
		_texture->GetHDC(), 0, 0, _texture->GetSize().x, _texture->GetSize().y, RGB(0, 0, 0));

}

void Animator::SetAnimeSize(int cx, int cy)
{
	_texture->SetSize(cx, cy);
}

int Animator::GetTextureImageNum()
{
	return _texture->GetNumOfCurrentTextureImage();
}

void Animator::ResetAnimeImageOrder()
{
	_texture->SetIndexOfImage(0);
}
