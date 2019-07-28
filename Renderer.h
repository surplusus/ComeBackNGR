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
	HDC _hdc;		// ���� �ѷ��ִ� handle
	HDC _backdc;	// ���� compatibleDC
	HDC _memdc;		// �׷��� ������ compatibleDC
	HBITMAP _backBit;
	HBITMAP _bit;
	std::map<int,HBITMAP> _himage ;
	BITMAP _image;
	PAINTSTRUCT ps;

	// �Լ������͸� �̿��� �������� ����
	//std::vector<void(Scene::*)(void)> _funcBackGround;
	//std::function<void()> f;
	// �ϴ��� ��� �׸��͵��� ������ ȣ���Ѵ�
	std::vector<void*> _sceneForBG;
	std::vector<InGamePart*> _partsForDraw;
public:
	//static std::vector<std::function<void()>> _funcDraw;
	//void AddListDrawFunc(std::function<void()> &draw);
	
	// ���� �ȿ� �������� Draw�� ȣ���ϸ� ��������Ѵ�
	void Render();	// ������ �׸��� �׸���(gameCenter�� ȣ��)
};

