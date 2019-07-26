#pragma once
class InGame;
class InGamePart;
// mediator
class PartsMgr
{
public:
	PartsMgr(InGame*);
	virtual ~PartsMgr();
	
private:
	InGame* _callerAsScene;
	// part ���� �����ߵȴ�
	std::vector<InGamePart*> _parts;
public:
	// part ���� �����ߵȴ�
	// part ���� ���鶧 this�� ���Խ�Ų��
	//void AddPart(InGamePart*);
	//void RemovePart(InGamePart*);
	void Mediate(InGamePart*);// �����ؾߵ�����
};

