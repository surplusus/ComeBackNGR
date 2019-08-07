#pragma once
#include "Scene.h"

class InGame : public Scene
{
public:
	InGame();
	virtual ~InGame();

private:
	PartsMgr* _partsMgr;
	SceneMgr* _sceneMgrptr;
	bool IsGameOver = false;
public:
	virtual void Init();
	virtual void Draw() override;
	virtual void Update();

	void IsGameOverOn();
};

