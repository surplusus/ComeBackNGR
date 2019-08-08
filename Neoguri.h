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
		JUMP_I,	JUMP_R, JUMP_L,
		CLIMB, IDLE, FALL, DIE};
	std::map<STATE, Animator*> _body;
	// M_ : �����̴� // S_ : ���ִ�
	STATE state = IDLE;
	bool isOnLadder = false;
	bool isGoingUp = false;
	bool isGoingDown = false;

	void KeepPosInside();
	void UpdatePosition();
	//STATE Jump(STATE);
	STATE MoveLR(STATE);
	STATE MoveUD(STATE);

	STATE Jump(STATE before, bool& goUp, bool& goDown);
	STATE DiePhase();
public:
	bool ToggleLadderState();	// �������� �θ�

	const POINT& GetPointNGR() const { return pos; }	// partMgr�� �θ�
	void Die();
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
		if (delay % 10000 == 0)
		{
			//Log("������ 10000ȸ");
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