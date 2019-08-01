#include "stdafx.h"
#include "Texture.h"
#include "Basic_Value.h"

TextureHandler::TextureHandler(int idImage, int countImageNum)
{
	// idImage : resource에 등록된 image의 첫번째 ID
	// countImageNum : idImage 이후에 resource에 등록된 이미지 갯수
	// resource.h 에 ID는 보통 차례로 등록되기 때문에 ++ 하면서 HBITMAP을 읽어들일 수 있다
	for (size_t i = 0; i < countImageNum; i++)
		_texture._images.push_back(LoadBitmap(g_hinst, MAKEINTRESOURCE(idImage + i)));

	_texture._hdc = CreateCompatibleDC(g_hmemdc);
	SelectObject(_texture._hdc, _texture._images[0]);
}

TextureHandler::~TextureHandler()
{
	for (auto bit : _texture._images)
	{
		DeleteObject((HBITMAP)bit);
	}
	DeleteObject(_texture._bit);
}

HBITMAP& TextureHandler::GetHBITMAP()
{
	return _texture._bit;
}

HDC& TextureHandler::GetHDC()
{
	SelectObject(_texture._hdc, _texture._bit);
	return _texture._hdc;
}

void TextureHandler::ChangeToNextBitmap()
{
	_texture._count = (_texture._count + 1) % _texture._images.size();
	_texture._bit = _texture._images[_texture._count];
}

POINT TextureHandler::GetSize()
{
	POINT re;
	re.x = _texture._rightbottom.x;
	re.y = _texture._rightbottom.y;
	return re;
}
