#include "stdafx.h"
#include "Texture.h"
#include "Basic_Value.h"

TextureHandler::TextureHandler(int idImage, int countImageNum)
{
	// idImage : resource�� ��ϵ� image�� ù��° ID
	// countImageNum : idImage ���Ŀ� resource�� ��ϵ� �̹��� ����
	// resource.h �� ID�� ���� ���ʷ� ��ϵǱ� ������ ++ �ϸ鼭 HBITMAP�� �о���� �� �ִ�
	for (int i = 0; i < countImageNum; i++)
		_texture._images.push_back(LoadBitmap(g_hinst, MAKEINTRESOURCE(idImage + i)));

	_texture._hdc = CreateCompatibleDC(g_hmemdc);
	SelectObject(_texture._hdc, _texture._images[0]);
}

TextureHandler::TextureHandler(std::string nameImage, int countImageNum)
{
	using std::string;
	using std::stringstream;
	// 1�� ������ ������ �ڸ���
	string st;
	stringstream ss;
	for (int i = 1; i <= countImageNum; ++i)
	{

		for (size_t j = 0; j < nameImage.size(); ++j)
		{
			if (nameImage[j] == '1')
				ss << i;
			else
				ss << nameImage[j];
		}

		st = ss.str();
		ss.str("");
		std::cout << st << std::endl;

		size_t origsize = st.length() + 1;
		size_t convertedChars = 0;
		wchar_t wcstring[30];
		mbstowcs_s(&convertedChars, wcstring, origsize, st.c_str(), _TRUNCATE);
		_texture._images.push_back((HBITMAP)
			LoadImage(NULL
				,wcstring
				, IMAGE_BITMAP
				, 0, 0
				, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
		ss.clear();
	}

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

void TextureHandler::SetSize(int cx, int cy)
{
	_texture._rightbottom.x = cx;
	_texture._rightbottom.y = cy;
}
