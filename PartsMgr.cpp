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
	return static_cast<Map*>(_parts.lower_bound(typeid(Map*))->second);
}

Neoguri * PartsMgr::GetNeoguri()
{
	return static_cast<Neoguri*>(_parts.lower_bound(typeid(Neoguri*))->second);
}

vector<Monster*> PartsMgr::GetMonsters()
{
	vector<Monster*> mon;
	for (auto it = _parts.lower_bound(typeid(Monster*)); it != _parts.upper_bound(typeid(Monster*)); it++)
		mon.emplace_back(static_cast<Monster*>(it->second));//xmemory.h오류잡은건가?
	return mon;
}

vector<Prey*> PartsMgr::GetPreys()
{
	vector<Prey*> prey;
	for (auto it = _parts.lower_bound(typeid(Prey*)); it != _parts.upper_bound(typeid(Prey*)); it++)
		prey.emplace_back(static_cast<Prey*>(it->second));
	return prey;
}

vector<Obstacle*> PartsMgr::GetObstacle()
{
	vector<Obstacle*> ob;
	for (auto it = _parts.lower_bound(typeid(Obstacle*)); it != _parts.upper_bound(typeid(Obstacle*)); it++)
		ob.emplace_back(static_cast<Obstacle*>(it->second));
	return ob;
}

void PartsMgr::AddMonster()
{
	InGamePart* mon = new Monster(this);
	_parts.insert(pair<type_index,InGamePart*>(typeid(mon),mon));
}

void PartsMgr::AddObstacle()
{
	InGamePart* obs = new Obstacle(this);
	_parts.insert(pair<type_index,InGamePart*>(typeid(obs), obs));
}

void PartsMgr::AddPrey()
{
	InGamePart* prey = new Prey(this);
	_parts.insert(pair<type_index,InGamePart*>(typeid(prey), prey));
}

void PartsMgr::Init()
{
	InGamePart* map = new Map(this);
#ifdef _DEBUG
	InGamePart* neoguri = new LoggedNeoguri(this);
#else
	InGamePart* neoguri = new Neoguri(this);
#endif // _DEBUG

	_parts.insert(pair<type_index,InGamePart*>(typeid(map), map));
	_parts.insert(pair<type_index,InGamePart*>(typeid(neoguri), neoguri));
}

void PartsMgr::Update()
{
	for (auto& part : _parts)
	{
		part.second->Update();
	}
}

