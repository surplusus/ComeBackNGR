#include "stdafx.h"
#include "Monster.h"
#include "Basic_Value.h"
// ���� ũ��� ���� 42, ���� 42

Monster::Monster(PartsMgr *mgr, int flr, int strX, int endX, int startDir)
	: InGamePart(mgr, strX, flr)
{
	movingSpeed = startDir;
	collider.UpdateCollider(strX, flr + 42, strX + 20, flr);
}

void Monster::Update()
{
	if (_startPatrolX >= pos.x ||
		_endPatrolX <= pos.x)
		movingSpeed = -movingSpeed;

	pos.x += movingSpeed;
	collider.UpdateCollider(pos);

	if (collider.OnNGRCollisionEnter())
		OnNotify(EVENTTYPE::DIE);
}