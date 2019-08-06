#include "stdafx.h"
#include "Texture.h"
#include "Basic_Value.h"

TextureHandler::TextureHandler(int idImage, int countImageNum)
{
	// idImage : resource에 등록된 image의 첫번째 ID
	// countImageNum : idImage 이후에 resource에 등록된 이미지 갯수
	// resource.h 에 ID는 보통 차례로 등록되기 때문에 ++ 하면서 HBITMAP을 읽어들일 수 있다
	for (int i = 0; i < countImageNum; i++)
		_texture._images.push_back(LoadBitmap(g_hinst, MAKEINTRESOURCE(idImage + i)));

	_texture._hdc = CreateCompatibleDC(g_hmemdc);
	SelectObject(_texture._hdc, _texture._images[0]);
}

TextureHandler::TextureHandler(std::string nameImage, int countImageNum)
{
	using std::string;
	using std::stringstream;
	// 1이 나오기 전까지 자르기
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
