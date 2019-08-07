#include "stdafx.h"
#include "InGame.h"
#include "Scene.h"

InGame::InGame()
{
}


InGame::~InGame()
{
	delete _partsMgr;
}

void InGame::Init()
{
	Renderer* R = Renderer::GetInstance();
	R->SelectBackGroundScene(R->T_INGAME);

	_sceneMgrptr = SceneMgr::GetInstance();

	_partsMgr = new PartsMgr(this);
	_partsMgr->Init();

}

void InGame::Draw()
{
	_partsMgr->Draw();
}

void InGame::Update()
{
	if (IsGameOver)
	{
		SceneMgr* s = SceneMgr::GetInstance();
		s->MoveToNextScene();
	}
	else
		_partsMgr->Update();
}

void InGame::IsGameOverOn()
{
	IsGameOver = true;
}