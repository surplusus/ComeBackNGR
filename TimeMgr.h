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
	const int T_TIMESIZE = 5;	// ��! �ؿ� T_TIME ���� �ݿ��ؾ���
public:
	enum T_TIME	{
		GAME =0,LIFE,NEOGURI,MONSTER,EYEMOVE
	};
	void SetPeriod(T_TIME);
	int DeltaTime(T_TIME);
	void AddTimer(T_TIME);
};

//// cf) system_clock ���� from_time,to_time �Լ��� �ִ�