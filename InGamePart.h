#pragma once
#include "Observer.h"
#include "ChainResponsibility.h"

class Chain;
class PartsMgr;
class InGamePart : public Subject, public Chain
{
public:
	InGamePart(PartsMgr*);
	virtual ~InGamePart() {}
protected:	// mediator와 상호작용 위해
	PartsMgr* _partsManager;

	KeyMgr* key = KeyMgr::GetInstance();
	SceneMgr* SnMgr = SceneMgr::GetInstance();
	TimeMgr* time = TimeMgr::GetInstance();
	Renderer* ren = Renderer::GetInstance();
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

