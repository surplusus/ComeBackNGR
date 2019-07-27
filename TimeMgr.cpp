#include "stdafx.h"
#include "TimeMgr.h"

TimeMgr* TimeMgr::instance = nullptr;

TimeMgr* TimeMgr::GetInstance()
{
	if (!instance) {
		instance = new TimeMgr;
		instance->Init();
	}
	return instance;
}

void TimeMgr::Release()
{
	TimeMgr* T = TimeMgr::GetInstance();

	for (auto timer : T->setTime)
		if (timer)
			delete timer;

	delete instance;
}

void TimeMgr::Init()
{
	setTime.resize(T_TIMESIZE);
	setTime[GAME] = new time_point<system_clock>;
	*setTime[GAME] = time.now();
}

void TimeMgr::SetPeriod(T_TIME t)
{
	AddTimer(t);
	*setTime[t] = time.now();
}

int TimeMgr::DeltaTime(T_TIME t)
{
	time_point<system_clock> endTime = time.now();

	setDeltaTime[t] = endTime - *setTime[t];

	return static_cast<int>(setDeltaTime[t].count());
}

void TimeMgr::AddTimer(T_TIME type)
{
	if (!setTime[type])
		setTime[type] = new time_point<system_clock>;
}
