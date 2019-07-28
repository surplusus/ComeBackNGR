#pragma once
class PartsMgr;
class InGamePart
{
public:
	InGamePart(PartsMgr*);
	virtual ~InGamePart();
protected:	// mediator와 상호작용 위해
	PartsMgr* _partsManager;

	virtual void Draw() {}
};

