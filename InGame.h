#pragma once
#include "Scene.h"

class InGame : public Scene
{
public:
	InGame();
	virtual ~InGame();

private:
	PartsMgr* _partsMgr;
public:
	virtual void Init();
	virtual void Draw();
	virtual void Update();
};

