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
};

