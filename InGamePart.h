#pragma once
#include "Observer.h"

class Collider;
class PartsMgr;

class InGamePart : public Subject
{
public:
	InGamePart(PartsMgr*, int x = 0, int numOfFloorOn = 0);
	virtual ~InGamePart() {}
protected:	// mediator와 상호작용 위해
	PartsMgr* _partsManager;

	KeyMgr* key = KeyMgr::GetInstance();
	SceneMgr* SnMgr = SceneMgr::GetInstance();
	TimeMgr* time = TimeMgr::GetInstance();
	Renderer* ren = Renderer::GetInstance();

	POINT pos;			//update시 위치도 해야한다
	Collider collider;	//update(움직이면), init(서있으면)시 충돌체도 해야한다(map빼고)
	int numOfFloorOn;
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

