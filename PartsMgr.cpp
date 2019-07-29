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

void PartsMgr::Mediate(InGamePart *inputpart)
{
	//if (inputpart == _parts[0])
	//{
	//	// do something
	//}
	//else if (inputpart == _parts[1])
	//{
	//	// do something
	//}

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
	InGamePart* neoguri = new Neoguri(this);
	_parts.insert(pair<type_index,InGamePart*>(typeid(map), map));
	_parts.insert(pair<type_index,InGamePart*>(typeid(neoguri), neoguri));
	/*_parts.insert(make_pair(typeid(map), map));
	_parts.insert(make_pair(typeid(Neoguri), neoguri));*/
}

