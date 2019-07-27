#pragma once
typedef struct _tagTexture
{
	std::vector<HBITMAP> _images;
	HBITMAP _bit;
	HDC _hdc;
	void MakeTexture(int idImage, int numSize);
	void ReleaseImage();
}TEXTURE;

void _tagTexture::MakeTexture(int idImage, int numSize)
{
	for (size_t i = 0; i < numSize; i++)
	{
		_images.push_back(LoadBitmap(g_hinst, MAKEINTRESOURCE(idImage + i)));
	}
}

inline void _tagTexture::ReleaseImage()
{
	for (auto bit : _images)
	{
		DeleteObject((HBITMAP)bit);
	}
	DeleteObject(_bit);
}