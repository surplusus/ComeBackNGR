#pragma once
#include "InGamePart.h"
class Animator;


class Neoguri : public InGamePart
{
public:
	Neoguri(PartsMgr*);
	virtual ~Neoguri() {}

	virtual void Update();
	virtual void Draw();
private:
	POINT _pos = { 700,465 };
	Animator* _body = nullptr;
	// M_ : �����̴� // S_ : ���ִ�
	enum STATE{M_LEFT, M_RIGHT, S_LEFT, S_RIGHT, 
		JUMP, CLIMP, IDLE, FALL, DIE};
	STATE state = IDLE;

	void KeepPosInside();
	void UpdatePosition();
	void UpdateBodyAnime();
	void Jump(STATE);
};

class LoggedNeoguri : public Neoguri
{
public:
	LoggedNeoguri(PartsMgr* mgr) : Neoguri(mgr){}
	inline virtual void Update() override {
		if (!updateFlag)
		{
			Log("�ʱ��� ������Ʈ");
			updateFlag = true;
		}
		Neoguri::Update();
		//	_wrapped.Update();// ��α׿��� ���ڷ����ͷ� ��ӹ��� ��ü�� �ɹ��� ������ �ִ´�
		// Neoguri�� �⺻ �����ڰ� ��� �̷��Ը� �Ẹ�Ҵ�.
	}
	inline virtual void Draw() override {
		static int delay = 0;
		delay++;
		if (delay % 4000 == 0)
		{
			Log("�ʱ��� ��ο�");
			delay = 0;
		}
		Neoguri::Draw();
	}
private:
	bool updateFlag = false;
	inline void Log(const char* message) {
		std::cout << message << std::endl;
	}
	//Neoguri& _wrapped;
};