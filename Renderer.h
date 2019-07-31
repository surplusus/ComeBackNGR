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
	HDC _hdc;		// 실제 뿌려주는 handle
	HDC _backdc;	// 배경용 compatibleDC
	HDC _memdc;		// 그려줄 목적의 compatibleDC
	HBITMAP _backBit;
	HBITMAP _bit;
	std::map<int,HDC> _himageDC ; // 배경용 compatibleDC
	BITMAP _image;
	//PAINTSTRUCT ps;

public:
	//EventBus* drawbus;
	//DrawBus* drawbus;
	enum TYPE_SCENE{T_OPENING, T_INGAME,T_ENDING};
	void Init();	
	void Render();	// 실질적으로 그림을 그린다(gameCenter가 호출)
	void SelectBackGroundScene(TYPE_SCENE);
};
