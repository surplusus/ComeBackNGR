#include "stdafx.h"
#include "KeyMgr.h"
#include "Map.h"
using std::cout;
using std::endl;

KeyMgr* KeyMgr::instance = nullptr;
EventBus* KeyMgr::eventbus = nullptr;

KeyMgr * KeyMgr::GetInstance()
{
	if (!instance)
	{
		instance = new KeyMgr;
		eventbus = new EventBus;
	}
	return instance;
}

void KeyMgr::Release()
{
	delete instance;
}

bool KeyMgr::HandleArrow()
{
	// 0000 0000 : 000[right] [left][down][up][space]
	if (GetAsyncKeyState(VK_UP)) {
		keyFlag |= K_UP;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		keyFlag |= K_DOWN;
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		keyFlag |= K_LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		keyFlag |= K_RIGHT;
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
		keyFlag |= 1;
	}

	if ((keyFlag & 1) != 0)
		IsSpacePushed = true;
	else 
		IsSpacePushed = false;

	return IsSpacePushed;
}
#pragma region Eventbus실험
bool KeyMgr::InputCheat()
{
	if (GetAsyncKeyState(VK_LBUTTON))
		if (GetAsyncKeyState(VK_RBUTTON))
		{
			keyFlag |= K_2MOUSE;
			// EventBus 만들어볼가?
			eventbus->Subscribe(this, &KeyMgr::OperateWhenCheatInput);
			return true;
		}
	return false;
}

void KeyMgr::OperateWhenCheatInput(CheatOperator * cheater)
{
	std::cout << "치트 발동" << std::endl;
	// 맵을 다음으로 넘긴다
	cheater->_map->GoToNextMap();
}
#pragma endregion
int KeyMgr::CheckKey()
{
	HandleArrow();
	HandleSpace();
	if (GetAsyncKeyState(VK_ESCAPE)) {
		keyFlag |= K_ESC;
	}
	int result = keyFlag;
	// 키 값을 가져갔으면 초기화
	IsArrowPushed = IsSpacePushed = keyFlag = false;
	return result;
}
