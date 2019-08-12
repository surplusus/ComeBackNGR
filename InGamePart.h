#pragma once
#include "Observer.h"

class Collider;
class PartsMgr;

class InGamePart : public Subject
{
public:
	InGamePart(PartsMgr*, int x = 0, int numOfFloorOn = 0);
	virtual ~InGamePart() {}
protected:	// mediator�� ��ȣ�ۿ� ����
	PartsMgr* _partsManager;

	KeyMgr* key = KeyMgr::GetInstance();
	SceneMgr* SnMgr = SceneMgr::GetInstance();
	TimeMgr* timer = TimeMgr::GetInstance();

	POINT pos;			//update�� ��ġ�� �ؾ��Ѵ�
	Collider collider;	//update(�����̸�), init(��������)�� �浹ü�� �ؾ��Ѵ�(map����)
	int numOfFloorOn;
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	const Collider* GetCollider() const { return &collider; }
};

