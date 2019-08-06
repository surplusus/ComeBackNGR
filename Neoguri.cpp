#include "stdafx.h"
#include "Neoguri.h"
#include "Basic_Value.h"
#include "Animator.h"

Neoguri::Neoguri(PartsMgr *mgr) : InGamePart(mgr, 700, FirstFloor)
{
	// 몸체 애니메이터 만들기
	_body[IDLE] = new Animator(IDB_BITMAP_IDLE1, 6);
	_body[M_LEFT] = new Animator(IDB_BITMAP_MLEFT1, 5);
	_body[M_RIGHT] = new Animator(IDB_BITMAP_MRIGHT1, 5);
	_body[FALL] = new Animator(IDB_BITMAP_FALL1, 4);
	_body[JUMP_R] = new Animator(IDB_BITMAP_RIGHTJUMP1, 8);
	_body[JUMP_L] = new Animator(IDB_BITMAP_LEFTJUMP1, 8);
	_body[CLIMP] = new Animator(IDB_BITMAP_CLIMB1, 2);
	_body[S_LEFT] = _body[M_LEFT];
	_body[S_RIGHT] = _body[M_RIGHT];
	_body[DIE] = _body[FALL];
	_body[JUMP_I] = _body[IDLE];

	// 너구리 처음 위치 body에 update
	for (auto &body : _body)
		body.second->UpdateAnimeCoord(pos.x, pos.y);

	TimeMgr* time = TimeMgr::GetInstance();
	time->SetPeriod("NEOGURI");
}

void Neoguri::Update()
{
	if (state != FALL)
	{
		UpdatePosition();
		UpdateBodyAnime();
	}
	else
	{
		DiePhase();
	}
	// 할일이 끝났으면 너구리 위치를 partMgr에게 알려주기
	InGamePart::_partsManager->SetNGRPosition(pos);
}

void Neoguri::Draw()
{
	switch (state)
	{
	case Neoguri::M_LEFT:
		_body[M_LEFT]->	DrawAnime(true,100);
		break;
	case Neoguri::M_RIGHT:
		_body[M_RIGHT]->DrawAnime(true, 100);
		break;
	case Neoguri::S_LEFT:
		_body[S_LEFT]->	DrawAnime(false, 100);
		break;
	case Neoguri::S_RIGHT:
		_body[S_RIGHT]->DrawAnime(false, 100);
		break;
	case Neoguri::JUMP_I:
		_body[IDLE]->	DrawAnime(true, 100);
		break;
	case Neoguri::JUMP_R:
		_body[JUMP_R]->	DrawAnime(true, 100);
		break;
	case Neoguri::JUMP_L:
		_body[JUMP_L]->	DrawAnime(true, 100);
		break;
	case Neoguri::CLIMP:
		_body[CLIMP]->	DrawAnime(true, 100);
		break;
	case Neoguri::IDLE:
		_body[IDLE]->DrawAnime(false, 100);
		break;
	case Neoguri::FALL:
		_body[FALL]->DrawAnime(true, 100);
		break;
	case Neoguri::DIE:
		_body[DIE]->DrawAnime(false, 100);
		break;
	default:
		break;
	}

}

void Neoguri::KeepPosInside()
{
	if (pos.x < MapMinWidth)	pos.x = MapMinWidth;
	if (pos.y < MapMinHeight)	pos.y = MapMinHeight;
	if (pos.x > MapMaxWidth) 	pos.x = MapMaxWidth;
	if (pos.y > MapMaxHeight)	pos.y = MapMaxHeight;
}

void Neoguri::UpdatePosition()
{
	if (state == FALL || state == DIE)
		return;

	int speed = 10;
	int keyFlag = key->CheckKey();

	if (time->Alarm("NEOGURIMOVE",40,0))
	{
		static STATE justBefore = IDLE;

		// 왼쪽 점프와 오른쪽 점프와 제자리 점프가 있어야한다
		if ((keyFlag & key->K_SPACE)) 
		{
			// 위로 올라가지도 않고 떨어지고 있지 않다면 점프 알림
			if (!isGoingUp && !isGoingDown)
			{
				state = JUMP;
				isGoingUp = true;
				Notify(EVENTTYPE::AIRTIME);
			}
		}

		// 위로 올라가고 있거나 전 동작이 올라가는 중이었다면 jump중
 		if (isGoingUp || isGoingDown)
		{
			justBefore = Jump(justBefore);
		}
		else
		{
			if (isOnLadder)
				justBefore = MoveUD(justBefore);
			else
				justBefore = MoveLR(justBefore);
		}
		
	}
	
	KeepPosInside();
}

void Neoguri::UpdateBodyAnime()
{
	_body[state]->UpdateAnimeCoord(pos.x, pos.y);
}

Neoguri::STATE Neoguri::Jump(STATE justBefore)
{
	int keyFlag = key->CheckKey();
	int jumpheight;
	int changeRateX;
	int changeRateY;
	STATE returnstate = justBefore;
	// 점프 입력이 처음 들어왔을때
	if (state == JUMP)
	{
		if (justBefore == M_LEFT || justBefore == S_LEFT)
			state = JUMP_L;
		if (justBefore == M_RIGHT || justBefore == S_RIGHT)
			state = JUMP_R;
		if (justBefore == IDLE)
			state = JUMP_I;
	}

	switch (state)
	{
		// 왼쪽 점프
		case Neoguri::JUMP_L :
		{
			// 작은 점프
			if (justBefore == S_LEFT)
			{
				jumpheight = 25;
				changeRateX = -5;
				changeRateY = -5;
			}
			// 높은 점프
			if (justBefore == M_LEFT)
			{
				jumpheight = 35;
				changeRateX = -7;
				changeRateY = -5;
			}
			
		}	break;
		// 오른쪽 점프
		case Neoguri::JUMP_R:
		{
			// 작은 점프
			if (justBefore == S_RIGHT)
			{
				jumpheight = 25;
				changeRateX = +5;
				changeRateY = -5;
			}
			// 높은 점프
			if (justBefore == M_RIGHT)
			{
				jumpheight = 35;
				changeRateX = +7;
				changeRateY = -5;
			}

		}	break;
		// 제자리 점프
		case Neoguri::JUMP_I:
		{
			// 작은 점프
			if (justBefore == IDLE)
			{
				jumpheight = 25;
				changeRateX = 0;
				changeRateY = -5;
			}
			
		}	break;
	}
	if (pos.y <= InGamePart::floor - jumpheight)
	{
		isGoingUp = false;
		isGoingDown = true;
	}

	pos.x += changeRateX;
	if (isGoingUp)
		pos.y += changeRateY;
	else
	{
		pos.y -= changeRateY;
		isGoingDown = true;
	}

	// 땅에 도착했는지 판단
	if (pos.y >= FirstFloor)
	{
		isGoingUp = isGoingDown = false;
		state = justBefore;
		Notify(LAND);
	}
	return justBefore;
}

Neoguri::STATE Neoguri::MoveLR(STATE justBefore)
{

	int speed = 10;
	int keyFlag = key->CheckKey();

	if (keyFlag & key->K_LEFT) {
		pos.x -= speed;
		state = M_LEFT;
	}
	else if (keyFlag & key->K_RIGHT) {
		pos.x += speed;
		state = M_RIGHT;
	}
	else if (!keyFlag)
	{
		if (justBefore == M_RIGHT)
			state = S_RIGHT;
		else if (justBefore == M_LEFT)
			state = S_LEFT;
		else
			state = justBefore;
	}
		return state;
}

Neoguri::STATE Neoguri::MoveUD(STATE)
{
	int keyFlag = key->CheckKey();
	int speed = 10;

	if (keyFlag & key->K_DOWN) {
		pos.y += speed;
		state = CLIMP;
	}
	else if (keyFlag & key->K_UP) {
		pos.y -= speed;
		state = CLIMP;
	}

	// 여러 층을 만들어야됨
	if (pos.y == 700)
	{
		state = IDLE;
		isOnLadder = false;
	}
	return IDLE;
}

Neoguri::STATE Neoguri::DiePhase()
{
	//떨어지는 모션 만들기
// 죽는 에니메이면 활성화(돌면서 떨어짐)
// 죽은 장소부터 y값 빼기
	return STATE::FALL;

// 바닥에 닿으면 멈춤
	return STATE::DIE;
}

void Neoguri::WhatToOperateWithChainID(int id)
{
	state = DIE;
}

bool Neoguri::ToggleOnLadder()
{
	bool justBeforeIsOnLadder = isOnLadder;
	isOnLadder = true;
	return justBeforeIsOnLadder;
}
