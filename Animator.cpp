#include "stdafx.h"
#include "Animator.h"
#include "Basic_Value.h"
#include "Texture.h"

#pragma comment (lib, "msimg32.lib")

void Animator::UpdateAnimeCoord(int x, int y)
{
	_coord.x += x;
	_coord.y += y;
	if (_coord.x < 0)				_coord.x = 0;
	if (_coord.y < 0)				_coord.y = 0;
	if (_coord.x > WindowWidth) 	_coord.x = WindowWidth;
	if (_coord.y > WindowHeight)	_coord.y = WindowHeight;
}

void Animator::MakeTexture(int idImage, int countImageNum)
{
	_texture = new TextureHandler(idImage, countImageNum);
}

void Animator::DrawAnime(bool isMoving)
{
	TimeMgr* time = TimeMgr::GetInstance();

	/*BitBlt(g_hmemdc,_coord.x,_coord.y,AnimeSizeWidth,AnimeSizeHeight,
		_texture->GetHDC(),*/
	
		
	if (isMoving && time->Alarm(time->ANIME, 500))
		_texture->ChangeToNextBitmap();

	TransparentBlt(g_hmemdc, _coord.x, _coord.y, AnimeSizeWidth, AnimeSizeHeight,
		_texture->GetHDC(), 0, 0, AnimeSizeWidth, AnimeSizeWidth, RGB(0, 0, 0));

}
