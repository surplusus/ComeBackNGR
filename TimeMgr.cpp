
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
	// ������ �˶����� ��� timer��� �����ش�
	if (timelist.find(timeName) != timelist.end()
		&& timelist[timeName].alarmFlag == 0)
		timelist.erase(timeName);
	// timer�� ���ٸ� �߰��Ѵ�
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
	// ���� �ݺ� ��ƾ
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

	// Alarm �Լ��� ó�� �θ� ��� ����
	AddTimer(timeName, cntRepeat);
	// [�ݺ� Ƚ�� > 0]�� �����ְ� [period]�� �Ǿ�����
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
