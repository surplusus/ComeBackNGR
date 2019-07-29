#include "stdafx.h"
#include "KeyMgr.h"
using std::cout;
using std::endl;
using std::pair;
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
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		cout << "up pushed" << endl;
		IsArrowPushed = true;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		cout << "down pushed" << endl;
		IsArrowPushed = true;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		cout << "left pushed" << endl;
		IsArrowPushed = true;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		cout << "right pushed" << endl;
		IsArrowPushed = true;
	}
	
	return IsArrowPushed;
}

bool KeyMgr::HandleSpace()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		cout << "SPACE pushed" << endl;
		IsArrowPushed = true;
	}

	return IsSpacePushed;
}

pair<bool, bool> KeyMgr::CheckKey()
{
	pair<bool,bool> p = pair<bool, bool>(IsArrowPushed, IsSpacePushed);
	p.first = HandleArrow();
	p.second = HandleSpace();
	IsArrowPushed = IsSpacePushed = false;
	return p;
}
