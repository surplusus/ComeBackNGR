#pragma once
#include <string>
// ������ interface�� �������� �� Ŭ����
class IEvent
{
};



////// IEvent�� ��ӹ޴� Ŭ������



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
		std::cout << "ġƮ�ߵ�" << std::endl;
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