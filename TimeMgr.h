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
	const int T_TIMESIZE = 5;	// 꼭! 밑에 T_TIME 수를 반영해야함
public:
	enum T_TIME	{
		GAME =0,LIFE,NEOGURI,MONSTER,EYEMOVE
	};
	void SetPeriod(T_TIME);
	int DeltaTime(T_TIME);
	void AddTimer(T_TIME);
};

//// cf) system_clock 에는 from_time,to_time 함수가 있다