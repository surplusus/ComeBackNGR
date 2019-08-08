#include "stdafx.h"
#include "InGame.h"
#include "InGamePart.h"
#include "Map.h"
#include "Prey.h"
#include "Monster.h"
#include "Obstacle.h"
#include "Neoguri.h"
#include "Observer.h"
#include "Basic_Value.h"
#pragma region using 선언
using std::make_pair;
using std::type_index;
using std::pair;
using std::vector;
using std::stringstream;
using std::cout;
using std::endl;
using std::string;
#pragma endregion
PartsMgr::PartsMgr(InGame *ingame)
{
	_callerAsScene = ingame;
}
PartsMgr::~PartsMgr()
{
	for (auto &part : _parts)
		delete part.second;
	_parts.clear();
}

#pragma region Getters
Neoguri * PartsMgr::GetNeoguri()
{
	return static_cast<Neoguri*>(_parts["Neoguri1"]);
}
//
//Map * PartsMgr::GetMap()
//{
//	return static_cast<Map*>(_parts["Map 1"]);
//}
//
//vector<Monster*> PartsMgr::GetMonsters()
//{
//	stringstream ss;
//	vector<Monster*> mon;
//	for (int i = 1; i <= 12; i++)
//	{
//		ss.str("");
//		ss << "Monster" << i;
//		auto it = _parts.find(ss.str());
//		if (_parts.find(ss.str()) != _parts.end())
//			if (it->second != nullptr)
//				mon.push_back(static_cast<Monster*>(_parts.find(ss.str())->second));
//	}
//
//	return mon;
//}
//
//vector<Prey*> PartsMgr::GetPreys()
//{
//	stringstream ss;
//	vector<Prey*> prey;
//	for (int i = 1; i <= 12; i++)
//	{
//		ss.str("");
//		ss << "Prey" << i;
//		auto it = _parts.find(ss.str());
//		if (it != _parts.end()) {
//			if (it->second != nullptr)
//				prey.push_back(static_cast<Prey*>(_parts.find(ss.str())->second));
//		}
//	}
//	return prey;
//}
//
//vector<Obstacle*> PartsMgr::GetObstacle()
//{
//	stringstream ss;
//	vector<Obstacle*> obs;
//	for (int i = 1; i <= 12; i++)
//	{
//		ss.str("");
//		ss << "Obstacle" << i;
//		auto it = _parts.find(ss.str());
//		if (_parts.find(ss.str()) != _parts.end())
//			if (it->second != nullptr)
//				obs.push_back(static_cast<Obstacle*>(_parts.find(ss.str())->second));
//	}
//	return obs;
//}
#pragma endregion Getters

#pragma region Adders
void PartsMgr::AddMonster(int flr, int srtX, int endX, int dir)
	// dir(음수) : move left// dir(양수) : move right// flr : floor
{
	string st = MakePartIndexName('m');
	// 기억해! firstfloor, secondfloor
	InGamePart* mon = new Monster(this,st, flr, srtX, endX, dir);
	//static_cast<Monster*>(mon)->SetPatrolCoordinate(srtX, endX);
	_parts[st] = mon;
#ifdef _DEBUG
	cout << st << " 생성" << endl;
#endif // _DEBUG
}

void PartsMgr::AddObstacle(int flr, int coordX)
{
	InGamePart* obs = new Obstacle(this, flr, coordX);
	string st = MakePartIndexName('O');
	_parts[st] = obs;
#ifdef _DEBUG
	cout << st << " 생성" << endl;
#endif // _DEBUG
}

void PartsMgr::AddPrey(int numOfFloorOn, int coordX)
{
	cntPrey = Prey::PreyMemberPtr.size();
	string st = MakePartIndexName('P');
	InGamePart* prey = new Prey(this,st, numOfFloorOn,coordX, cntPrey);
#ifdef _DEBUG
	int stringSize = st.size();
	int forCheckTmp = atoi(st.c_str() + stringSize - 1);
	if (cntPrey == forCheckTmp)
		cout << "만들때 먹이 인덱스 == 매니저가 관리하는 인덱스" << endl;
	else
		cout << "만들때 먹이 인덱스 <> 매니저가 관리하는 인덱스" << endl;
#endif // _DEBUG

	_parts[st] = prey;
#ifdef _DEBUG
	cout << st << " 생성" << endl;
#endif // _DEBUG

}
void PartsMgr::AddMap(int num)
{
	string st = MakePartIndexName('B', num);
	InGamePart* map = new Map(this);
#ifdef _DEBUG
	cout << st << " 생성" << endl;
#endif // _DEBUG
	_parts[st] = map;
}
#pragma endregion Adders

std::string PartsMgr::MakePartIndexName(const char name, int num)
{
	stringstream ss;
	switch (name)
	{
	case	'p':
	case	'P':
		ss << "Prey";
		if (num == -1)		ss << ++cntPrey;
		else				ss << num;
		break;
	case	'm':
	case	'M':
		ss << "Monster";
		if (num == -1)		ss << ++cntMon;
		else				ss << num;
		break;
	case	'o':
	case	'O':
		ss << "Obstacle";
		if (num == -1)		ss << ++cntObs;
		else				ss << num;
		break;
	case	'B':
	case	'b':
		ss << "Map";
		if (num == -1)		ss << ++cntObs;
		else				ss << num;
		break;
	}

	return ss.str();
}

void PartsMgr::MakeDrawOrder()
{
	if (isDrawOrderDirty)
	{
		_partsOrderList.clear();
		stringstream ss;
		//// 맵을 먼저 그리고(B : background)
		ss << MakePartIndexName('B', numOfCurrentMap);
		_partsOrderList.push_back(_parts[ss.str()]);
		ss.str("");
		//// 장애물 그리고(O : Obstacle)
		for (int i = 1; i <= 12; ++i)
		{
			ss << MakePartIndexName('O', i);
			if (_parts.find(ss.str()) != _parts.end())
				_partsOrderList.push_back(_parts[ss.str()]);
			ss.str("");
		}
		//// 너구리 그리기
		ss << "Neoguri1";
		_partsOrderList.push_back(_parts[ss.str()]);
		ss.str("");
		//// 먹이 그리고
		for (int i = 1; i <= 12; ++i)
		{
			ss << MakePartIndexName('P', i);
			if (_parts.find(ss.str()) != _parts.end())
				_partsOrderList.push_back(_parts[ss.str()]);
			ss.str("");
		}
		//// 몬스터 그리고
		for (int i = 1; i <= 12; ++i)
		{
			ss << MakePartIndexName('M', i);
			if (_parts.find(ss.str()) != _parts.end())
				_partsOrderList.push_back(_parts[ss.str()]);
			ss.str("");
		}
		isDrawOrderDirty = false;
	}
}

void PartsMgr::Init()
{
	AddMap(1);	// 1번째 맵 만들기
	string stNeo = "Neoguri1";
#ifdef _DEBUG
	InGamePart* neoguri = new LoggedNeoguri(this);
	_parts[stNeo] = neoguri;
	cout << stNeo << " 생성" << endl;
#else
	InGamePart* neoguri = new Neoguri(this);
#endif // _DEBUG
	// 먹이를 먹었을때 이벤트 등록
	EventBus::GetInstance()->Subscribe(this, &PartsMgr::RemovePrey);
	// 맵 구성하기 (firstfloor : 465, // dir(음수) : move left// dir(양수) : move right// flr : floor)
	// 나중에 JSON을 읽어와서 처리하기
	AddMonster(FirstFloor, 200, 400, 1);
	//AddMonster(SecondFloor, 200, 400, 2);
	//AddMonster(ThirdFloor, 200, 400, 3);
	//AddMonster(FourthFloor, 200, 400, 5);
	AddMonster(FifthFloor, 200, 400, 6);
	AddPrey(FirstFloor, 500);
	//AddPrey(FirstFloor, 600);
	AddObstacle(FirstFloor, 100);
}

void PartsMgr::Draw()
{
	MakeDrawOrder();
	for (auto &parts : _partsOrderList)
		parts->Draw();
}

void PartsMgr::Update()
{
	_posNGR = static_cast<Neoguri*>(_parts["Neoguri1"])->GetPointNGR();
	for (auto& part : _partsOrderList)
		part->Update();
}

void PartsMgr::OnNotifyEvent(Subject * sub, int evetType)
{
	switch (evetType)
	{
		case EVENTTYPE::NONE:
			break;
		case EVENTTYPE::DIE:
			cout << "우왕주금" << endl;
			_callerAsScene->IsGameOverOn();
			break;
		case EVENTTYPE::MONSTER:
			GetNeoguri()->Die();
			break;
		case EVENTTYPE::OBSTACLE:
			GetNeoguri()->Die();
			break;
		case EVENTTYPE::NOPRAYLEFT:
			break;
		case EVENTTYPE::AIRTIME:
			cout << "Jumping" << endl;
			break;
		case EVENTTYPE::LAND:
			cout << "Land : " << endl;
			break;
		case EVENTTYPE::LADDER:
			cout << "ladder" << endl;
			GetNeoguri()->ToggleLadderState();
			break;
		case EVENTTYPE::NEXTSTAGE:
			cout << "go to next stage" << endl;
			break;
	}
}

void PartsMgr::RemovePrey(EventPreyRemove * evnt)
{
	stringstream ss;
	for (int i = 1; i <= 12; i++)
	{
		ss.str("");
		ss << "Prey" << i;
		auto it = _parts.find(ss.str());
		if (it != _parts.end()) {
			delete it->second;
			_parts.erase(it);
			isDrawOrderDirty = true;
		}
	}
}
