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
			Log("너구리 업데이트");
			updateFlag = true;
		}
		Neoguri::Update();
		//	_wrapped.Update();// 블로그에선 데코레이터로 상속받은 객체를 맴버로 가지고 있는다
		// Neoguri에 기본 생성자가 없어서 이렇게만 써보았다.
	}
	inline virtual void Draw() override {
		Log("너구리 드로우");
		Neoguri::Draw();
	}
private:
	bool updateFlag = false;
	inline void Log(const char* message) {
		std::cout << message << std::endl;
	}
	//Neoguri& _wrapped;
};