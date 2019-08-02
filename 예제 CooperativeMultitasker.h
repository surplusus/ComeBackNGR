#pragma once
#include <memory>
#include <list>

class Process;
typedef std::shared_ptr<Process> StrongProcessPtr;
typedef std::weak_ptr<Process> WeakProcessPtr;

//===========Process Interface====================//
class Process
{
	friend class ProcessManager;

public:
	enum State
	{
		UNINITIALIZED = 0,
		REMOVED,
		RUNNING,
		PAUESED,
		SUCCEEDED,
		FAILED,
		ABORTED,
	};
private:
	State m_state;
	StrongProcessPtr m_pChild;
public:
	Process();
	virtual ~Process();

protected:
	virtual void VOnInit() { m_state = RUNNING; }
	virtual void VOnSuccess() {}
	virtual void VOnFail() {}
	virtual void VOnAbort() {}
	virtual void VOnUpdate(unsigned long deltaMs) = 0;
	
public:
	inline void Succeed();
	inline void Fail();

	inline void Pause();
	inline void UnPause();

	State GetState() const { return m_state; }
	bool IsAlive() const { return (m_state == RUNNING || m_state == ABORTED); }
	bool IsDead() const {
		return (m_state == SUCCEEDED || m_state == FAILED || m_state == ABORTED);
	}
	bool IsRemoved() const { return (m_state == REMOVED); }
	bool IsPaused() const { return (m_state == PAUESED); }

	inline void AttachChild(StrongProcessPtr pChild);
	StrongProcessPtr RemoveChild();
	StrongProcessPtr PeekChild() { return m_pChild; }

private:
	void SetState(State newState) { m_state = newState; }
};

//===========ProcessManager Interface====================//
class ProcessManager
{
	typedef std::list<StrongProcessPtr> ProcessList;
private:
	ProcessList m_processList;
public:
	virtual ~ProcessManager();

	unsigned int UpdateProcesses(unsigned long deltaMs);
	WeakProcessPtr AttachProcess(StrongProcessPtr pProcess);
	void AbortAllProcesses(bool immediate);

	unsigned int GetProcessCount() const { return m_processList.size(); }

private:
	void ClearAllProcesses();
};


//===========Process Concrete====================//
class DelayProcess : public Process
{
	unsigned long m_timeToDelay;
	unsigned long m_timeDelayedSoFar;

public:
	explicit DelayProcess(unsigned long timeToDelay)  {
		m_timeToDelay = timeToDelay;
		m_timeDelayedSoFar = 0;
	}

protected:
	virtual void VOnUpdate(unsigned long deltaMs)	{
		m_timeDelayedSoFar += deltaMs;
		if (m_timeDelayedSoFar >= m_timeToDelay)
			Succeed();
	}
};

class KaboomProcess;
//===========main 활용 예제====================//
int main()
{
	ProcessManager processManager;

	StrongProcessPtr pDelay(new DelayProcess(3000));
	processManager.AttachProcess(pDelay);

	// KaboomProcess가 DelayProcess의 AttachChild되어있기 때문에 
	// DelayProcess가 Success()를 호출할때까지 기다린다.
	// 만약 기다렸는데도 DalyProcess가 Success() 하지 못하면 
	// KaboomProcess는 업데이트 못하고 지워진다.
	StrongProcessPtr pKaboom(new KaboomProcess());
	pDelay->AttachChild(pKaboom);

	return 0;
}