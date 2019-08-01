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
	Animator* _body = nullptr;
	enum STATE{M_LEFT,M_RIGHT,JUMP,CLIMP,IDLE,FALL,DIE};
	STATE state = IDLE;
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
		Log("�ʱ��� ��ο�");
		Neoguri::Draw();
	}
private:
	bool updateFlag = false;
	inline void Log(const char* message) {
		std::cout << message << std::endl;
	}
	//Neoguri& _wrapped;
};