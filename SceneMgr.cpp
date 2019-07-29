#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "InGame.h"

SceneMgr* SceneMgr::instance = nullptr;

SceneMgr * SceneMgr::GetInstance()
{
	if (!instance)
		instance = new SceneMgr;
	return instance;
}

void SceneMgr::Release()
{
	delete instance;
}


void SceneMgr::ChangeScene(Scene *s)
{
	_scene = s;
}

void SceneMgr::Init()
{
	v_Scenes.resize(3);

	v_Scenes[OPEN] = new Opening;
	v_Scenes[GAME] = new InGame;
	v_Scenes[END] = new Ending;

	_scene = v_Scenes[OPEN];
}

void SceneMgr::Update()
{
	if (v_Scenes[_sceneNum] == _scene)
		return;
	else
		_sceneNum++;

	//-> sceneMgr가 추가적으로 해야할 일
}
