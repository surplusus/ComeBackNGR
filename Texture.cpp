#include "stdafx.h"
#include "Texture.h"
#include "Basic_Value.h"

TextureHandler::TextureHandler(int idImage, int countImageNum)
{
	// idImage : resource�� ��ϵ� image�� ù��° ID
	// countImageNum : idImage ���Ŀ� resource�� ��ϵ� �̹��� ����
	// resource.h �� ID�� ���� ���ʷ� ��ϵǱ� ������ ++ �ϸ鼭 HBITMAP�� �о���� �� �ִ�
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

inline HBITMAP TextureHandler::GetHBITMAP()
{
	return _texture._bit;
}

inline HDC TextureHandler::GetHDC()
{
	SelectObject(_texture._hdc, _texture._bit);
	return _texture._hdc;
}

void TextureHandler::ChangeToNextBitmap()
{
	_texture._count = (_texture._count + 1) % _texture._images.size();
	_texture._bit = _texture._images[_texture._count];
}
