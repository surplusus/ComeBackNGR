#include "stdafx.h"
#include "GameCenter.h"

GameCenter::GameCenter()
{
	InitAll();
}

void GameCenter::OperateProcedure()
{
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
	try
	{
		_key = KeyMgr::GetInstance();
		_scene = SceneMgr::GetInstance();
		_render = Renderer::GetInstance();
		_time = TimeMgr::GetInstance();
		_sound = SoundMgr::GetInstance();

		_sound->Init();
		_render->Init();
		_scene->Init();

	}
	catch (const std::exception& e)
	{
#ifdef _DEBUG
		cout << e.what() << endl;
		cout << "GameCenter : can not be Initiated." << endl;
		cout << "GameCenter : has nullptr!!!" << endl;
#endif // _DEBUG
	}
}
