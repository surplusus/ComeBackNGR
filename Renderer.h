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
	HDC _hdc;		// ���� �ѷ��ִ� handle
	HDC _backdc;	// ���� compatibleDC
	HDC _memdc;		// �׷��� ������ compatibleDC
	HBITMAP _backBit;
	HBITMAP _bit;
	std::map<int,HBITMAP> _himage ;
	BITMAP _image;
	PAINTSTRUCT ps;

	std::vector<void(InGamePart::*)(void)> _funcDraw;
	std::vector<void(Scene::*)(void)> _funcBackGround;
public:
	void LoadBGImageFromFile(LPWSTR pFileName);	// �޹���� ���� �׸���(Scene�� ȣ��)
	void ListUpDrawFunc(void(InGamePart::*)(void));
	void ListUpBackGroundDrawFunc(void(Scene::*)(void));

	void Render();	// ������ �׸��� �׸���(gameCenter�� ȣ��)
};

