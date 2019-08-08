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
protected:
	enum STATE{M_LEFT, M_RIGHT, S_LEFT, S_RIGHT,
		JUMP_I,	JUMP_R, JUMP_L,
		CLIMB, IDLE, FALL, DIE};
	std::vector<int> floorList;
	RECT boundary[2];
	std::map<STATE, Animator*> _body;
	// M_ : �����̴� // S_ : ���ִ�
	STATE state = IDLE;
	bool isOnLadder = false;
	bool isGoingUp = false;
	bool isGoingDown = false;

	void UpdatePosition();
	STATE DiePhase();
	STATE MoveLR(STATE);
	STATE MoveUD(STATE);
	STATE Jump(STATE before, bool& goUp, bool& goDown);
	int ChangeNumOfFloorOn();
	void KeepPosInside();
public:
	virtual bool ToggleLadderState();	// �������� �θ�

	const POINT& GetPointNGR() const { return pos; }	// partMgr�� �θ�
	void Die();
};

class LoggedNeoguri : public Neoguri
{
public:
	LoggedNeoguri(PartsMgr* mgr) : Neoguri(mgr){}
		//	_wrapped.Update();// ��α׿��� ���ڷ����ͷ� ��ӹ��� ��ü�� �ɹ��� ������ �ִ´�
		// Neoguri�� �⺻ �����ڰ� ��� �̷��Ը� �Ẹ�Ҵ�.
	inline virtual bool ToggleLadderState() override {
		if (Neoguri::ToggleLadderState() &&
			timer->Alarm("LADDERLOG",2000,-1))
			Log("Ladder On");

		return isOnLadder;
	}
	inline virtual void Draw() override {
		if (timer->Alarm("NGRDRAW",10000,10))
		{
			Log("�ʱ��� ��ο�");
		}
		Neoguri::Draw();
	}
private:
	TimeMgr* timer = TimeMgr::GetInstance();
	inline void Log(const char* message) {
		std::cout << message << std::endl;
	}
	//Neoguri& _wrapped;
};