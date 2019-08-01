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

	/*for (auto timer : T->setTime)
		delete timer.second;*/

	delete instance;
}

void TimeMgr::Init()
{
	AddTimer("GAME");
}

void TimeMgr::SetPeriod(std::string timeName)
{
	AddTimer(timeName);
}

int TimeMgr::DeltaTime(std::string timeName)
{
	time_point<system_clock> endTime = time.now();
	
	AddTimer(timeName);

	timelist[timeName].l_deltaTime = endTime - timelist[timeName].setTime;
	timelist[timeName].n_deltaTime = static_cast<int>(timelist[timeName].l_deltaTime.count()) * 1000;

	// 1 millisecond
	
	if (timelist[timeName].n_deltaTime > 10000000)
		timelist[timeName].n_deltaTime -= 10000000;
	
	return timelist[timeName].n_deltaTime;
}

int TimeMgr::Alarm(std::string timeName, int period, int cntRepeat)
{
	// Alarm 함수를 처음 부를 경우 생성
	if (timelist.find(timeName) == timelist.end())
		timelist[timeName] = S_TIME(time.now(), cntRepeat);

	if (timelist[timeName].alarmFlag)
	{
		if (DeltaTime(timeName) >= period)
		{
			timelist[timeName].alarmFlag--;
			timelist[timeName].setTime = time.now();
			return timelist[timeName].alarmFlag;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		timelist.erase(timeName);
		return -1;
	}
}

void TimeMgr::AddTimer(std::string timeName)
{
	if (timelist.find(timeName) == timelist.end())
		timelist[timeName] = S_TIME(time.now());
}
