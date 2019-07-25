#include "stdafx.h"
#include "TimeMgr.h"

TimeMgr* TimeMgr::instance = nullptr;

TimeMgr * TimeMgr::GetInstance()
{
	if (!instance)
		instance = new TimeMgr;
	return instance;
}

void TimeMgr::Release()
{
	delete instance;
}
