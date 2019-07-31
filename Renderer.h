#pragma once
#include "Observer.h"

class Scene;
class InGamePart;

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
	HDC _hdc;		// ���� �ѷ��ִ� handle
	HDC _backdc;	// ���� compatibleDC
	HDC _memdc;		// �׷��� ������ compatibleDC
	HBITMAP _backBit;
	HBITMAP _bit;
	std::map<int,HDC> _himageDC ; // ���� compatibleDC
	BITMAP _image;
	//PAINTSTRUCT ps;

public:
	//EventBus* drawbus;
	//DrawBus* drawbus;
	enum TYPE_SCENE{T_OPENING, T_INGAME,T_ENDING};
	void Init();	
	void Render();	// ���������� �׸��� �׸���(gameCenter�� ȣ��)
	void SelectBackGroundScene(TYPE_SCENE);
};
