#pragma once
class PartsMgr;
class InGamePart
{
public:
	InGamePart(PartsMgr*);
	virtual ~InGamePart();
protected:	// mediator�� ��ȣ�ۿ� ����
	PartsMgr* _partsManager;

	virtual void Draw() {}
};

