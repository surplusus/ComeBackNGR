#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "InGame.h"

SceneMgr* SceneMgr::instance = nullptr;

SceneMgr * SceneMgr::GetInstance()
{
	if (!instance)
	{
		instance = new SceneMgr;

	}
	return instance;
}

void SceneMgr::Release()
{
	delete instance;
}


void SceneMgr::ChangeScene(Scene *s)
{
	_curScene = s;
	_curScene->Init();
}

void SceneMgr::Init()
{
	v_Scenes.resize(3);

	v_Scenes[OPEN] = new Opening;
	v_Scenes[GAME] = new InGame;
	v_Scenes[END] = new Ending;

	_sceneNum = OPEN;

	ChangeScene(v_Scenes[OPEN]);
}

void SceneMgr::Update()
{
	_curScene->Update();
}

void SceneMgr::MoveToNextScene()
{
	_sceneNum++;
	if (_sceneNum >= 3)
		exit(0);
	else
		ChangeScene(v_Scenes[_sceneNum]);
}

void SceneMgr::DrawScene()
{
	_curScene->Draw();
}
