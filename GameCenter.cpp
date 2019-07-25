#include "stdafx.h"
#include "GameCenter.h"

GameCenter * GameCenter::GetInstance()
{
	if (!instance)
		instance = new GameCenter();
	
	return instance;
}

void GameCenter::Release()
{
	delete instance;
}

void GameCenter::ChangeScene(Scene *s)
{
	_scene = s;
}

void GameCenter::Init()
{
	_scene = new Scene;
}
