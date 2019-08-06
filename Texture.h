#pragma once

typedef struct _tagTexture
{
	std::vector<HBITMAP> _images;
	int _count = 0;
	HBITMAP _bit;
	HDC _hdc;
	POINT _rightbottom = { 42,48 };
}TEXTURE;

class TextureHandler
{
private:
	TEXTURE _texture;

public:
	TextureHandler(int idImage, int countImageNum);
	TextureHandler(std::string, int countImageNum);
	~TextureHandler();

	HBITMAP& GetHBITMAP();
	HDC& GetHDC();
	void ChangeToNextBitmap();
	POINT GetSize();
	void SetSize(int cx, int cy);
};
