#pragma once
#include "Observer.h"

class Collider;
class Chain;
class PartsMgr;

class InGamePart : public Subject, public Chain
{
public:
	InGamePart(PartsMgr*, int x = 0, int floor = 0);
	virtual ~InGamePart() {}
protected:	// mediator�� ��ȣ�ۿ� ����
	PartsMgr* _partsManager;

	KeyMgr* key = KeyMgr::GetInstance();
	SceneMgr* SnMgr = SceneMgr::GetInstance();
	TimeMgr* time = TimeMgr::GetInstance();
	Renderer* ren = Renderer::GetInstance();

	POINT pos;			//update�� ��ġ�� �ؾ��Ѵ�
	Collider collider;	//update(�����̸�), init(��������)�� �浹ü�� �ؾ��Ѵ�(map����)
	int floor;
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

