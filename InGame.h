#pragma once
class Scene;

class InGame : public Scene//(�ҿ���������?)
{
public:
	InGame();
	virtual ~InGame();

private:
	PartsMgr* _partsMgr;
public:
	void Draw(HDC);
};

