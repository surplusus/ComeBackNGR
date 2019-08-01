#include "stdafx.h"
#include "KeyMgr.h"
using std::cout;
using std::endl;

KeyMgr* KeyMgr::instance = nullptr;

KeyMgr * KeyMgr::GetInstance()
{
	if (!instance)
		instance = new KeyMgr;
	return instance;
}

void KeyMgr::Release()
{
	delete instance;
}

bool KeyMgr::HandleArrow()
{
	// 0000 0000 : 000[right] [left][down][up][space]
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		keyFlag |= 2;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		keyFlag |= 4;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		keyFlag |= 8;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		keyFlag |= 16;
	}
	
	if ((keyFlag & 30) != 0)
		IsArrowPushed = true;
	else IsArrowPushed = false;

	return IsArrowPushed;
}

bool KeyMgr::HandleSpace()
{
	// 0000 0000 : 000[right] [left][down][up][space]
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		cout << "SPACE pushed" << endl;
		keyFlag |= 1;
	}

	if ((keyFlag & 1) != 0)
		IsSpacePushed = true;
	else 
		IsSpacePushed = false;

	return IsSpacePushed;
}

int KeyMgr::CheckKey()
{
	HandleArrow();
	HandleSpace();
	int result = keyFlag;
	// 키 값을 가져갔으면 초기화
	IsArrowPushed = IsSpacePushed = keyFlag = false;
	return result;
}
