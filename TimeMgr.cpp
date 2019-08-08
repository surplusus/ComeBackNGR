
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
	delete instance;
}

void TimeMgr::Init()
{
	AddTimer("GAME");
}

void TimeMgr::SetPeriod(std::string timeName)
{
	// 예전에 알람으로 썼던 timer라면 지워준다
	if (timelist.find(timeName) != timelist.end()
		&& timelist[timeName].alarmFlag == 0)
		timelist.erase(timeName);
	// timer가 없다면 추가한다
	AddTimer(timeName);
}

int TimeMgr::DeltaTime(std::string timeName)
{
	time_point<system_clock> endTime = time.now();
	
	AddTimer(timeName);

	timelist[timeName].l_deltaTime = endTime - timelist[timeName].setTime;
	// 1 millisecond
	timelist[timeName].n_deltaTime = static_cast<int>(timelist[timeName].l_deltaTime.count() * 1000);
	
	return timelist[timeName].n_deltaTime;
}

int TimeMgr::Alarm(std::string timeName, int period, int cntRepeat)
{
	// 무한 반복 루틴
	if (cntRepeat == 0)
	{
		AddTimer(timeName);
		if (DeltaTime(timeName) >= period)
		{
			timelist[timeName].setTime = time.now();
			return 1;
		}
		return 0;
	}

	// Alarm 함수를 처음 부를 경우 생성
	AddTimer(timeName, cntRepeat);
	// [반복 횟수 > 0]가 남아있고 [period]가 되었을때
	if ((timelist[timeName].alarmFlag >= 0) 
		&& (DeltaTime(timeName) >= period))
	{
		timelist[timeName].setTime = time.now();
		timelist[timeName].alarmFlag--;
		return timelist[timeName].alarmFlag;
	}
	if (timelist[timeName].alarmFlag == 0)
		timelist.erase(timelist.find(timeName));
	return 0;
}

void TimeMgr::AddTimer(std::string timeName, int cntRepeat)
{
	if (cntRepeat == -1)
	{
		if (timelist.find(timeName) == timelist.end())
			timelist[timeName] = S_TIME(time.now());
	}
	else
	{
		if (timelist.find(timeName) == timelist.end())
			timelist[timeName] = S_TIME(time.now(), cntRepeat);
	}
}
