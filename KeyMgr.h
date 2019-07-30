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
	int keyFlag = 0;

	bool HandleArrow();
	bool HandleSpace();
public:
	// 0000 0000 : 000[right] [left][down][up][space]
	int CheckKey();

	enum{K_SPACE = 1, K_UP = 2, K_DOWN = 4, K_LEFT = 8, K_RIGHT = 16};
};

