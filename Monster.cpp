#include "stdafx.h"
#include "Monster.h"
#include "Basic_Value.h"
#include "Animator.h"
// 몬스터 크기는 가로 42, 세로 42

Monster::Monster(PartsMgr *mgr, int flr, int startX, int endX, int startDir)
	: InGamePart(mgr, startX, flr), _startPatrolX(startX), _endPatrolX(endX)
{
	movingSpeed = startDir;
	body["LEFT"] = new Animator("image/monster/monleft1.bmp", 2);
	body["LEFT"]->SetAnimeSize(42, 42);
	body["RIGHT"] = new Animator("image/monster/monright1.bmp", 2);
	body["RIGHT"]->SetAnimeSize(42, 42);

	if (movingSpeed >= 0)
	{
		_curBody = body["RIGHT"];
		pos = { startX + 21, flr };
	}
	else
	{
		_curBody = body["LEFT"];
		pos = { endX - 21, flr };
	}

	collider.UpdateCollider(pos.x-10, pos.y, pos.x + 10, pos.y + 40);
}

void Monster::Update()
{
	if (_startPatrolX > pos.x || _endPatrolX < pos.x)
		movingSpeed = -movingSpeed;

	if (movingSpeed >= 0)
		_curBody = body["RIGHT"];
	else
		_curBody = body["LEFT"];

	pos.x += movingSpeed;
	_curBody->UpdateAnimeCoord(pos.x, pos.y);
	collider.UpdateCollider(pos);

	if (collider.OnNGRCollisionEnter())
		Notify(EVENTTYPE::MONSTER);
}

void Monster::Draw()
{
	_curBody->DrawAnime(true, 360);
}
