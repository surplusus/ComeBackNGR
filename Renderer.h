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
	HDC _hdc;		// ���� �ѷ��ִ� handle
	HDC _backdc;	// ���� compatibleDC
	HDC _memdc;		// �׷��� ������ compatibleDC
	HBITMAP _backBit;
	HBITMAP _bit;
	std::map<int,HDC> _himageDC ; // ���� compatibleDC
	BITMAP _image;
	PAINTSTRUCT ps;

	// �Լ������͸� �̿��� �������� ����
	//std::vector<void(Scene::*)(void)> _funcBackGround;
	//std::function<void()> f;
	// �ϴ��� ��� �׸��͵��� ������ ȣ���Ѵ�
	EventBus* _eventbus = nullptr;
	std::vector<void*> _sceneForBG;
	std::vector<InGamePart*> _partsForDraw;
	
public:
	enum TYPE_SCENE{T_OPENING, T_INGAME,T_ENDING};
	void Init();	
	//static std::vector<std::function<void()>> _funcDraw;
	//void AddListDrawFunc(std::function<void()> &draw);
	
	// ���� �ȿ� �������� Draw�� ȣ���ϸ� ��������Ѵ�
	void Render();	// ������ �׸��� �׸���(gameCenter�� ȣ��)
	void SelectBackGroundScene(TYPE_SCENE);
};
