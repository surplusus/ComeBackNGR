#include "stdafx.h"
#include "KeyMgr.h"

KeyMgr* KeyMgr::instance = nullptr;

KeyMgr * KeyMgr::GetInstance()
{
	if (!instance)
		instance = new KeyMgr;
	return instance;
}

void KeyMgr::Release()
{
	delete instance;
}
