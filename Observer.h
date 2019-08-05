#pragma once
#include <vector>
class Subject;

class Observer
{
protected:
	int eventmask = 0;
public:
	virtual ~Observer() = default;
	virtual void ReceiveEvent(Subject*,int) = 0;

	inline void ToggleOnEventMask(int idEvent){
		eventmask &= idEvent;
	}
	inline void ToggleOffEventMask(int idEvent) {
		eventmask &= ~idEvent;
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
	void OnNotify(int eventtype) {
		for (auto o : observer)
			o->ReceiveEvent(this, eventtype);
	}
};
