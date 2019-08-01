#pragma once
#include <ctime>	
#include <chrono>
using namespace std::chrono;
typedef struct _tagTime
{
	time_point<system_clock> setTime;
	duration<double> l_deltaTime;
	int n_deltaTime;
	int alarmFlag = -1;
	explicit _tagTime() {}
	explicit _tagTime(time_point<system_clock> now) 
		: setTime(now) {}
	explicit _tagTime(time_point<system_clock> now, int cnt)
		: setTime(now), alarmFlag(cnt) {}
}S_TIME;

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
	std::map<std::string, S_TIME> timelist;
	void Init();

	// DeltaTime("GAME")으로 게임 시작부터 시간을 구한다
public:
	// 시간 재기 시작
	void SetPeriod(std::string timeName);
	// 잰 Daltatime 반환
	int DeltaTime(std::string timeName);
	// 시간마다 알람 설정(단기적으로쓴다)
	int Alarm(std::string timeName, int period, int cntRepeat);

private:
	void AddTimer(std::string);
};

//// cf) system_clock 에는 from_time,to_time 함수가 있다