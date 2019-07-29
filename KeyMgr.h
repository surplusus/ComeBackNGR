#pragma once
class KeyMgr
{
private:
	static KeyMgr* instance;
	KeyMgr() {}
	~KeyMgr() {}
public:
	static KeyMgr* GetInstance();
	static void Release();
private:
	bool IsArrowPushed = false;
	bool IsSpacePushed = false;

	bool HandleArrow();
	bool HandleSpace();
public:
	std::pair<bool, bool> CheckKey();
};

