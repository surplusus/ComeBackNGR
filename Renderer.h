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
	void LoadBGImageFromFile(LPWSTR pFileName);	// �޹���� ���� �׸���(Scene�� ȣ��)
	void Render(void(*draw)(HDC&));	// ������ �׸��� �׸���(gameCenter�� ȣ��)
	
};

