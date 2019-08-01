#include "stdafx.h"
#include "InGame.h"
#include "InGamePart.h"
#include "Map.h"
#include "Prey.h"
#include "Monster.h"
#include "Obstacle.h"
#include "Neoguri.h"
using std::make_pair;
using std::type_index;
using std::pair;
using std::vector;
using std::stringstream;
using std::cout;
using std::endl;
using std::string;

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

void PartsMgr::AddMonster()
{
	static int cnt = 0;
	string st = "Monster ";
	stringstream ss;
	ss >> ++cnt;
	ss << st;

	InGamePart* mon = new Monster(this);
	_parts[st] = mon;
	cout << st << " 积己" << endl;
}

void PartsMgr::AddObstacle()
{
	static int cnt = 0;
	string st = "Obstacle ";
	stringstream ss;
	ss >> ++cnt;
	ss << st;

	InGamePart* obs = new Obstacle(this);
	_parts[st] = obs;
	cout << st << " 积己" << endl;
}

void PartsMgr::AddPrey()
{
	static int cnt = 0;
	string st = "Prey ";
	stringstream ss;
	ss >> ++cnt;
	ss << st;

	InGamePart* prey = new Prey(this);
	_parts[st] = prey;
	cout << st << " 积己" << endl;
}

void PartsMgr::Init()
{
	string stNeo = "Neoguri 1";
	string stMap = "Map 1";

	InGamePart* map = new Map(this);
#ifdef _DEBUG
	InGamePart* neoguri = new LoggedNeoguri(this);
#else
	InGamePart* neoguri = new Neoguri(this);
#endif // _DEBUG
	
	_parts[stMap] = map;
	cout << stMap << " 积己" << endl;
	_parts[stNeo] = neoguri;
	cout << stNeo << " 积己" << endl;
}

void PartsMgr::Draw()
{
	// 甘阑 刚历 弊府绊
	GetMap()->Draw();
	// 冈捞 弊府绊
	for (auto &prey : GetPreys())
		prey->Draw();
	// 阁胶磐 弊府绊
	for (auto &mon : GetMonsters())
		mon->Draw();
	// 呈备府 弊府扁
	GetNeoguri()->Draw();
}

void PartsMgr::Update()
{
	for (auto& part : _parts)
	{
		part.second->Update();
	}
}

