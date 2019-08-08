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
	EventNGRKeepIn(const std::string direction) : dir(direction) {}
	std::string GetOuterDirection() { return dir; }
private:
	std::string dir;
};

class EventPreyRemove : public IEvent{
public:
	EventPreyRemove(shared_ptr<InGamePart> p) : prey(p) {}
	shared_ptr<InGamePart> GetPreyPtr() { return prey; }
private:
	shared_ptr<InGamePart> prey;
};

