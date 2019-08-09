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