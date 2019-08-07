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
Map * PartsMgr::GetMap()
{
	return static_cast<Map*>(_parts["Map 1"]);
}

Neoguri * PartsMgr::GetNeoguri()
{
	return static_cast<Neoguri*>(_parts["Neoguri 1"]);
}

vector<Monster*> PartsMgr::GetMonsters()
{
	string st = "Monster";
	stringstream ss;
	int cnt = 0;
	vector<Monster*> mon;

	while (true) {
		ss << st << ++cnt;
		
		if (_parts.find(ss.str()) != _parts.end())
			mon.push_back(static_cast<Monster*>(_parts.find(ss.str())->second));
		else
			break;
		ss.str("");
	}

	return mon;
}

vector<Prey*> PartsMgr::GetPreys()
{
	string st = "Prey";
	stringstream ss;
	int cnt = 0;
	vector<Prey*> prey;

	while (true) {
		ss << st << ++cnt;
		if (_parts.find(ss.str()) != _parts.end())
			prey.push_back(static_cast<Prey*>(_parts.find(ss.str())->second));
		else
			break;
		ss.str("");
	}

	return prey;
}

vector<Obstacle*> PartsMgr::GetObstacle()
{
	string st = "Obstacle";
	stringstream ss;
	int cnt = 0;
	vector<Obstacle*> obs;

	while (true) {
		ss << st << ++cnt;
		if (_parts.find(ss.str()) != _parts.end())
			obs.push_back(static_cast<Obstacle*>(_parts.find(ss.str())->second));
		else
			break;
		ss.str("");
	}

	return obs;
}
#pragma endregion Getters

#pragma region Adders
void PartsMgr::AddMonster(int flr, int srtX, int endX, int dir)
	// dir(음수) : move left// dir(양수) : move right// flr : floor
{
	string st = MakeMapIndexName('m');
	// 기억해! firstfloor, secondfloor
	InGamePart* mon = new Monster(this, flr, srtX, endX, dir);
	//static_cast<Monster*>(mon)->SetPatrolCoordinate(srtX, endX);
	_parts[st] = mon;
#ifdef _DEBUG
	cout << st << " 생성" << endl;
#endif // _DEBUG
}

void PartsMgr::AddObstacle(int flr, int coordX)
{
	InGamePart* obs = new Obstacle(this, flr, coordX);
	string st = MakeMapIndexName('O');
	_parts[st] = obs;
#ifdef _DEBUG
	cout << st << " 생성" << endl;
#endif // _DEBUG
}

void PartsMgr::AddPrey(int numOfFloorOn, int coordX)
{
	cntPrey = Prey::PreyMemberPtr.size();
	string st = MakeMapIndexName('P');
	InGamePart* prey = new Prey(this, numOfFloorOn,coordX, cntPrey);
#ifdef _DEBUG
	int stringSize = st.size();
	int forCheckTmp = atoi(st.c_str() + stringSize - 1);
	cout << forCheckTmp << endl;
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
#pragma endregion Adders

std::string PartsMgr::MakeMapIndexName(const char name, int num)
{
	stringstream ss;
	if (name == 'p' || name == 'P')
	{
		ss << "Prey";
		if (num == -1)		ss << ++cntPrey;
		else				ss << num;
	}
	if (name == 'm' || name == 'M')
	{
		ss << "Monster";
		if (num == -1)		ss << ++cntMon;
		else				ss << num;
	}
	if (name == 'o' || name == 'O')
	{
		ss << "Obstacle";
		if (num == -1)		ss << ++cntObs;
		else				ss << num;
	}
	return ss.str();
}

//void PartsMgr::MakeChain()
//{
//	// When DIE
//	Chain::AddNextSuccessor(_parts["Neoguri 1"], EVENTTYPE::DIE);
//	// 모든 몬스터 멈춤
//	for (int i = 1; i <= cntMon; ++i)
//	{
//		string name = MakeMapIndexName('m', i);
//		Chain::AddNextSuccessor(_parts[name], EVENTTYPE::DIE);
//	}
//
//	// 다른 체인이 필요하면 아래에 미리 만들어두기
//}

void PartsMgr::Init()
{
	string stNeo = "Neoguri 1";
	string stMap = "Map 1";

	InGamePart* map = new Map(this);
#ifdef _DEBUG
	InGamePart* neoguri = new LoggedNeoguri(this);
	_parts[stMap] = map;
	cout << stMap << " 생성" << endl;
	_parts[stNeo] = neoguri;
	cout << stNeo << " 생성" << endl;
#else
	InGamePart* neoguri = new Neoguri(this);
#endif // _DEBUG
	//책임연쇄 만들기
	//MakeChain();	
	// 맵 구성하기 (firstfloor : 465, // dir(음수) : move left// dir(양수) : move right// flr : floor)
	AddMonster(FirstFloor, 200, 400, 1);
	//AddMonster(SecondFloor, 200, 400, 2);
	//AddMonster(ThirdFloor, 200, 400, 3);
	//AddMonster(FourthFloor, 200, 400, 5);
	//AddMonster(FifthFloor, 200, 400, 6);
	AddPrey(FirstFloor, 500);
	//AddPrey(FirstFloor, 500);
	AddObstacle(FirstFloor, 100);
}

void PartsMgr::Draw()
{
	// 맵을 먼저 그리고
	GetMap()->Draw();
	// 장애물 그리고
	for (auto &obs : GetObstacle())
		obs->Draw();
	// 너구리 그리기
	GetNeoguri()->Draw();
	// 먹이 그리고
	for (auto &prey : GetPreys())
		prey->Draw();
	// 몬스터 그리고
	for (auto &mon : GetMonsters())
		mon->Draw();
}

void PartsMgr::Update()
{
	_posNGR = static_cast<Neoguri*>(_parts["Neoguri 1"])->GetPointNGR();
	for (auto& part : _parts)
		part.second->Update();
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
			cout << "Land" << endl;
			break;
		case EVENTTYPE::LADDER:
			cout << "ladder" << endl;
			break;
		case EVENTTYPE::NEXTSTAGE:
			cout << "go to next stage" << endl;
			break;
	}
}

