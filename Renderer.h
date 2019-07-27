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
	HDC _hdc;		// 실제 뿌려주는 handle
	HDC _backdc;	// 배경용 compatibleDC
	HDC _memdc;		// 그려줄 목적의 compatibleDC
	HBITMAP _backBit;
	HBITMAP _bit;
	std::map<int,HBITMAP> _himage ;
	BITMAP _image;
	PAINTSTRUCT ps;

	std::vector<void(InGamePart::*)(void)> _funcDraw;
	std::vector<void(Scene::*)(void)> _funcBackGround;
public:
	void LoadBGImageFromFile(LPWSTR pFileName);	// 뒷배경을 먼저 그린다(Scene이 호출)
	void ListUpDrawFunc(void(InGamePart::*)(void));
	void ListUpBackGroundDrawFunc(void(Scene::*)(void));

	void Render();	// 나머지 그림을 그린다(gameCenter가 호출)
};

