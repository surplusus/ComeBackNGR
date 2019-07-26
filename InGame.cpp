#include "stdafx.h"
#include "InGame.h"


InGame::InGame()
{
	_partsMgr = new PartsMgr(this);
}


InGame::~InGame()
{
}
