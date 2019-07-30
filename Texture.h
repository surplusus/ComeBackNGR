#pragma once

typedef struct _tagTexture
{
	std::vector<HBITMAP> _images;
	HBITMAP _bit;
	HDC _hdc;
}TEXTURE;

class TextureHandler
{
public:
	TextureHandler(int idImage, int countImageNum);
	~TextureHandler();

	TEXTURE _texture;
};
