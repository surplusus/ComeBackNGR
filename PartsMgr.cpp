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
#pragma region using ����
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
	string st = "Monster ";
	stringstream ss(st);
	int cnt = 0;
	vector<Monster*> mon;

	while (true) {
		ss >> ++cnt;
		ss << st;
		if (_parts.find(st) != _parts.end())
			mon.push_back(static_cast<Monster*>(_parts.find(st)->second));
		else
			break;
	}

	return mon;
}

vector<Prey*> PartsMgr::GetPreys()
{
	string st = "Prey ";
	stringstream ss(st);
	int cnt = 0;
	vector<Prey*> prey;

	while (true) {
		ss >> ++cnt;
		ss << st;
		if (_parts.find(st) != _parts.end())
			prey.push_back(static_cast<Prey*>(_parts.find(st)->second));
		else
			break;
	}

	return prey;
}

vector<Obstacle*> PartsMgr::GetObstacle()
{
	string st = "Obstacle ";
	stringstream ss(st);
	int cnt = 0;
	vector<Obstacle*> obs;

	while (true) {
		ss >> ++cnt;
		ss << st;
		if (_parts.find(st) != _parts.end())
			obs.push_back(static_cast<Obstacle*>(_parts.find(st)->second));
		else
			break;
	}

	return obs;
}

void PartsMgr::AddMonster(int x, int y, int srtX, int endX, int dir)
	// dir(0) : M_LEFT // dir(1) : M_RIGHT
{
	string st = MakeMapIndexName('O');
	POINT p = { x,y };
	InGamePart* mon = new Monster(this, p, dir);
	static_cast<Monster*>(mon)->SetPatrolCoordinate(srtX, endX);
	_parts[st] = mon;
#ifdef _DEBUG
	cout << st << " ����" << endl;
#endif // _DEBUG
}

void PartsMgr::AddObstacle()
{
	InGamePart* obs = new Obstacle(this);
	string st = MakeMapIndexName('O');
	_parts[st] = obs;
#ifdef _DEBUG
	cout << st << " ����" << endl;
#endif // _DEBUG
}

void PartsMgr::AddPrey()
{
	InGamePart* prey = new Prey(this);
	string st = MakeMapIndexName('P');
	_parts[st] = prey;
#ifdef _DEBUG
	cout << st << " ����" << endl;
#endif // _DEBUG

}

std::string PartsMgr::MakeMapIndexName(const char name, int num)
{
	string st;
	stringstream ss;
	if (name == 'p' || name == 'P')
	{
		st = "Prey ";
		if (num == -1)		ss >> ++cntPrey;
		else				ss >> num;
		ss << st;
	}
	if (name == 'm' || name == 'M')
	{
		st = "Monster ";
		if (num == -1)		ss >> ++cntMon;
		else				ss >> num;
		ss << st;
	}
	if (name == 'o' || name == 'O')
	{
		st = "Obstacle ";
		if (num == -1)		ss >> ++cntObs;
		else				ss >> num;
		ss << st;
	}
	return st;
}

void PartsMgr::MakeChain()
{
	// When DIE
	Chain::AddNextSuccessor(_parts["Neoguri 1"], EVENTTYPE::DIE);
	// ��� ���� ����
	for (int i = 1; i <= cntMon; ++i)
	{
		string name = MakeMapIndexName('m', i);
		Chain::AddNextSuccessor(_parts[name], EVENTTYPE::DIE);
	}

	// �ٸ� ü���� �ʿ��ϸ� �Ʒ��� �̸� �����α�
}

void PartsMgr::Init()
{
	string stNeo = "Neoguri 1";
	string stMap = "Map 1";

	InGamePart* map = new Map(this);
#ifdef _DEBUG
	InGamePart* neoguri = new LoggedNeoguri(this);
	_parts[stMap] = map;
	cout << stMap << " ����" << endl;
	_parts[stNeo] = neoguri;
	cout << stNeo << " ����" << endl;
#else
	InGamePart* neoguri = new Neoguri(this);
#endif // _DEBUG
	//å�ӿ��� �����
	MakeChain();	
}

void PartsMgr::Draw()
{
	// ���� ���� �׸���
	GetMap()->Draw();
	// ��ֹ� �׸���
	for (auto &obs : GetObstacle())
		obs->Draw();
	// ���� �׸���
	for (auto &prey : GetPreys())
		prey->Draw();
	// ���� �׸���
	for (auto &mon : GetMonsters())
		mon->Draw();
	// �ʱ��� �׸���
	GetNeoguri()->Draw();
}

void PartsMgr::Update()
{
	for (auto& part : _parts)
	{
		part.second->Update();
	}
}

void PartsMgr::ReceiveEvent(Subject * sub, int evetType)
{
	switch (evetType)
	{
		case EVENTTYPE::NONE:
			break;
		case EVENTTYPE::DIE:
			Chain::OperateChain(DIE);
			break;
		case EVENTTYPE::MONSTER:
			break;
		case EVENTTYPE::OBSTACLE:
			break;
		case EVENTTYPE::PRAY:
			break;
		case EVENTTYPE::AIRTIME:
			break;
		case EVENTTYPE::LAND:
			break;
		case EVENTTYPE::LADDER:
			cout << "ladder" << endl;
			break;
	}
}

