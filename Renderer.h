#pragma once
#include "Observer.h"
class Scene;
class InGamePart;

class Renderer : public EventBus
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

	// 함수포인터를 이용한 옵저버는 보류
	//std::vector<void(Scene::*)(void)> _funcBackGround;
	//std::function<void()> f;
	// 일단은 모든 그릴것들을 일일이 호출한다
	std::vector<void*> _sceneForBG;
	std::vector<InGamePart*> _partsForDraw;
public:
	//static std::vector<std::function<void()>> _funcDraw;
	//void AddListDrawFunc(std::function<void()> &draw);
	
	// 벡터 안에 포인터의 Draw를 호출하면 지워줘야한다
	void Render();	// 나머지 그림을 그린다(gameCenter가 호출)
};

