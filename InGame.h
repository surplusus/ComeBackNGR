#pragma once
class Scene;

class InGame : public Scene//(불완전한형식?)
{
public:
	InGame();
	virtual ~InGame();

private:
	PartsMgr* _partsMgr;
public:
	void Draw(HDC);
};

