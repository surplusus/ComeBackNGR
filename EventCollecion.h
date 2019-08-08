#pragma once
#include <string>
// 공통의 interface를 쓰기위한 빈 클래스
class IEvent
{
};



////// IEvent를 상속받는 클래스들



class EventDIE : public IEvent{
public:
	void p() {
		std::cout << s << std::endl;
	}

private:
	std::string s = "test";
};

class EventCheatOperator : public IEvent{
public:
	bool isOnCheat;
	inline bool GetCheat() {
		std::cout << "치트발동" << std::endl;
		return isOnCheat;
	}
	EventCheatOperator(bool cheat)
		: isOnCheat(cheat) {}
};

class EventNGRKeepIn : public IEvent{
public:
	EventNGRKeepIn();
	~EventNGRKeepIn();

private:

};

class EventPreyRemove : public IEvent{
public:
	EventPreyRemove(Prey* p) : prey(p) {}
	Prey* GetPreyPtr() { return prey; }
private:
	Prey* prey;
};