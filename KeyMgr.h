#pragma once
class EventCheatOperator;
class Map;
class EventBus;

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
public:
	bool HandleArrow();
	bool HandleSpace();
	bool InputCheat();
public:
	// 0000 0000 : 00[ESC][right] [left][down][up][space]
	int CheckKey();

	enum{K_SPACE  = 1,		//0000 0000 0001
		K_UP	  = 2,		//0000 0000 0010
		K_DOWN	  = 4,		//0000 0000 0100
		K_LEFT	  = 8,		//0000 0000 1000
		K_RIGHT	  = 16,		//0000 0001 0000
		K_ESC	  = 32,		//0000 0010 0000
		K_2MOUSE  = 192		//0000 1100 0000
	};
};
