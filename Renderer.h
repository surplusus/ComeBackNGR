#pragma once
class Renderer
{
private:
	static Renderer* instance;
	Renderer() {}
	~Renderer() {}
public:
	static Renderer* GetInstance();
	static void Release();
private:
	HDC _hdc;
	HDC _memdc;
	HBITMAP _bit;
	HBITMAP _oldbit;
	BITMAP _image;
public:
	void LoadBGImageFromFile(LPWSTR pFileName);
	
	void Render();
};

