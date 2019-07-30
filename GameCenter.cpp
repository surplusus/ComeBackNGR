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
	_key->CheckKey();
	_scene->Update();
	_render->Render();
}

void GameCenter::ReleaseProcedure()
{
	_key->Release();
	_scene->Release();
	_render->Release();
	_time->Release();
}

void GameCenter::Init()
{
	_key = KeyMgr::GetInstance();
	_scene = SceneMgr::GetInstance();
	_render = Renderer::GetInstance();
	_time = TimeMgr::GetInstance();
	if (!_key || !_scene || !_render || !_time)
		cout << "GameCenter : has nullptr!!!" << endl;

	//_key->Init();
	_scene->Init();
	_render->Init();

}
