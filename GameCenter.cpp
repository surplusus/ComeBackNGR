#include "stdafx.h"
#include "GameCenter.h"
using std::cout;
using std::endl;

GameCenter::GameCenter()
{
	Init();
}

void GameCenter::OperateProcedure()
{
	_key->Update();
	_scene->Update();
	Render();
}

void GameCenter::Render()
{
	_render->Render();
}

void GameCenter::Init()
{
	_key = KeyMgr::GetInstance();
	_scene = SceneMgr::GetInstance();
	_render = Renderer::GetInstance();
	_time = TimeMgr::GetInstance();
	if (!_key || !_scene || !_render || !_time)
		cout << "GameCenter : Init failed!!!" << endl;
}
