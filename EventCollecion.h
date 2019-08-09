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
	EventPreyRemove(std::shared_ptr<Prey> p) : prey(p) {}
	std::shared_ptr<Prey> GetPreyPtr() { return prey; }
private:
	std::shared_ptr<Prey> prey;
};

class EventSoundPlay : public IEvent{
public:
	EventSoundPlay(int idSound) : id(idSound) {}
	SoundMgr* GetSMGR() { return S; }
	int GetSoundID() { return id; }
private:
	SoundMgr* S = SoundMgr::GetInstance();
	int id;
};