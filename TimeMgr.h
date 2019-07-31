#pragma once
#include <ctime>	
#include <chrono>
using namespace std::chrono;

class TimeMgr
{
private:
	static TimeMgr* instance;
	TimeMgr() {}
	~TimeMgr() {}
public:
	static TimeMgr* GetInstance();
	static void Release();
private:
	system_clock time;
	std::vector<time_point<system_clock>*> setTime;
	std::vector<duration<double>> setDeltaTime;

	void Init();
public:
	enum T_TIME	{
		GAME =0,LIFE,NEOGURI,MONSTER,EYEMOVE,ANIME,
		T_TIMECOUNT
	};
	void SetPeriod(T_TIME);	// 시간 재기 시작
	int DeltaTime(T_TIME);	// 잰 Daltatime 반환
	bool Alarm(T_TIME, int);// 시간마다 알람 설정
private:
	void AddTimer(T_TIME);
};

//// cf) system_clock 에는 from_time,to_time 함수가 있다