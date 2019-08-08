#include "stdafx.h"
#include "Monster.h"
#include "Basic_Value.h"
#include "Animator.h"
// 몬스터 크기는 가로 42, 세로 42

Monster::Monster(PartsMgr *mgr, std::string n, int flr, int startX, int endX, int startDir)
	: InGamePart(mgr), _startPatrolX(startX), _endPatrolX(endX), name(n)
{	
	movingSpeed = startDir;
	body["LEFT"] = new Animator(name, "image/monster/monleft1.bmp", 2);
	body["LEFT"]->SetAnimeSize(42, 42);
	body["RIGHT"] = new Animator(name, "image/monster/monright1.bmp", 2);
	body["RIGHT"]->SetAnimeSize(42, 42);

	if (movingSpeed >= 0)
	{
		_curBody = body["RIGHT"];
		pos = { startX, flr + 10 };
	}
	else
	{
		_curBody = body["LEFT"];
		pos = { endX, flr + 10 };
	}
	// 중앙점과 그리는 점은 다름 (중하단 : pos) (좌상단 : 그리기 기준점)
	body["LEFT"]->UpdateAnimeCoord(pos.x - 21, pos.y - 52);
	body["RIGHT"]->UpdateAnimeCoord(pos.x - 21, pos.y - 52);
	RECT re = { 0,0,20,50 };
	collider.UpdateCollider(re);
	collider.UpdateCollider(pos);
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
	// 중앙점과 그리는 점은 다름 (중하단 : pos) (좌상단 : 그리기 기준점)
	_curBody->UpdateAnimeCoord(pos.x - 21, pos.y - 52);
	collider.UpdateCollider(pos);

	if (PtInRect(&collider.GetColliderRect(), _partsManager->GetNGRPosition()))
		Notify(EVENTTYPE::MONSTER);
}

void Monster::Draw()
{
	_curBody->DrawAnime(true, 100);

#ifdef _DEBUG
	RECT r = collider.GetColliderRect();
	FillRect(g_hmemdc, &r, (HBRUSH)GetStockObject(GRAY_BRUSH));
#endif // _DEBUG

}
