#include "stdafx.h"
#include "GameCenter.h"
#include "FMOD Studio API Windows/api/core/inc/fmod.h"
using std::cout;
using std::endl;

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

void GameCenter::LoadSound()
{
	//FMOD_System_CreateSound()
}

void GameCenter::InitAll()
{
	_key = KeyMgr::GetInstance();
	_scene = SceneMgr::GetInstance();
	_render = Renderer::GetInstance();
	_time = TimeMgr::GetInstance();
	_sound = SoundMgr::GetInstance();
	if (!_key || !_scene || !_render || !_time)
		cout << "GameCenter : has nullptr!!!" << endl;

	//LoadSound();
	_sound->Init();
	_render->Init();
	_scene->Init();

}
