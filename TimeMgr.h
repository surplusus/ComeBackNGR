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

	// DeltaTime("GAME")���� ���� ���ۺ��� �ð��� ���Ѵ�
public:
	// �ð� ��� ����
	void SetPeriod(std::string timeName);
	// �� Daltatime ��ȯ
	int DeltaTime(std::string timeName);
	// �ð����� �˶� ����(�ܱ������ξ���)
	int Alarm(std::string timeName, int period, int cntRepeat);

private:
	void AddTimer(std::string);
};

//// cf) system_clock ���� from_time,to_time �Լ��� �ִ�