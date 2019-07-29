#include "stdafx.h"
#include "InGame.h"
#include "Scene.h"

InGame::InGame()
{
	Init();
}


InGame::~InGame()
{
}

void InGame::Init()
{
	_partsMgr = new PartsMgr(this);
}

void InGame::Draw()
{
}

void InGame::Update()
{
}
