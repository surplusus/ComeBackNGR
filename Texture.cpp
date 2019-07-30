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

}

TextureHandler::~TextureHandler()
{
	for (auto bit : _texture._images)
	{
		DeleteObject((HBITMAP)bit);
	}
	DeleteObject(_texture._bit);
}
