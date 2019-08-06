#include "stdafx.h"
#include "GameCenter.h"
#include "Basic_Value.h"
using std::cout;
using std::endl;

GameCenter::GameCenter()
{
	InitAll();
}

void GameCenter::OperateProcedure()
{
	if ((_key->CheckKey() & _key->K_ESC))
		SendMessage(g_hwnd, WM_DESTROY, 0, 0);
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

void GameCenter::InitAll()
{
	_key = KeyMgr::GetInstance();
	_scene = SceneMgr::GetInstance();
	_render = Renderer::GetInstance();
	_time = TimeMgr::GetInstance();
	if (!_key || !_scene || !_render || !_time)
		cout << "GameCenter : has nullptr!!!" << endl;

	//_key->Init();
	_render->Init();
	_scene->Init();

}
