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
	void SetPeriod(T_TIME);	// �ð� ��� ����
	int DeltaTime(T_TIME);	// �� Daltatime ��ȯ
	bool Alarm(T_TIME, int);// �ð����� �˶� ����
private:
	void AddTimer(T_TIME);
};

//// cf) system_clock ���� from_time,to_time �Լ��� �ִ�