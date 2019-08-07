#pragma once
#include <vector>
class Subject;

class EventCallSystem
{
public:
	void EventCallQueueUp(std::function<void()> call) {
		funclist.push_back(call);
	}
	void Operate() {
		// 후입 선출
		funclist.back()();
		funclist.pop_back();
	}
private:
	std::vector<std::function<void()>> funclist;
};

class Observer
{
protected:
	EventCallSystem eventcaller;
public:
	virtual ~Observer() = default;
	virtual void OnNotifyEvent(Subject*,int) = 0;

	void QueueOnNotifyEvent(std::function<void()> call) {
		eventcaller.EventCallQueueUp(call);
	}
	void OperateAllStackedEvent() {
		eventcaller.Operate();
	}
};

class Subject
{
private:
	std::vector<Observer*> observer;
protected:
	virtual ~Subject() = default;
	void Register(Observer* o) {
		observer.push_back(o);
	}
	void UnRegister(Observer* o) {
		auto it = std::find(observer.begin(), observer.end(), o);
		observer.erase(it);
	}
	// observer 부분
	void Notify(int eventtype) {
		for (auto o : observer)
			o->OnNotifyEvent(this, eventtype);
	} 
	// EventCallSystem 부분
	void NotyfyEventCall(std::function<void()> call) {
		for (auto o : observer)
			o->QueueOnNotifyEvent(call);
	}
};
