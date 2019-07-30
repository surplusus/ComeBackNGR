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
