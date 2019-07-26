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
	enum {NEOGURI=1,

	};
	HDC _hdc;
	HDC _backdc;
	HDC _memdc;
	HBITMAP _backBit;
	HBITMAP _bit;
	std::map<int,HBITMAP> _himage ;
	BITMAP _image;
	PAINTSTRUCT ps;
public:
	void LoadBGImageFromFile(LPWSTR pFileName);	// 뒷배경을 먼저 그린다(Scene이 호출)
	void Render(void(*draw)(HDC&));	// 나머지 그림을 그린다(gameCenter가 호출)
	
};

