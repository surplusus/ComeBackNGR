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
	enum STATE{M_LEFT, M_RIGHT, S_LEFT, S_RIGHT, 
		JUMP, CLIMP, IDLE, FALL, DIE};
	POINT _pos = { 700,465 };
	std::map<STATE, Animator*> _body;
	// M_ : 움직이는 // S_ : 서있는
	STATE state = IDLE;

	void KeepPosInside();
	void UpdatePosition();
	void UpdateBodyAnime();
	//STATE Jump(STATE);
	STATE Move(STATE);
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
		static int delay = 0;
		delay++; 
		if (delay % 10000 == 0)
		{
			//Log("프레임 10000회");
			Log("너구리 드로우");
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