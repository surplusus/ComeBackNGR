#include "stdafx.h"
#include "Neoguri.h"
#include "Basic_Value.h"
#include "Animator.h"

Neoguri::Neoguri(PartsMgr *mgr) : InGamePart(mgr)
{
	// ��ü �ִϸ����� �����
	_body[IDLE] = new Animator;
	_body[M_LEFT] = new Animator;
	_body[M_RIGHT] = new Animator;
	_body[S_LEFT] = _body[M_LEFT];
	_body[S_RIGHT] = _body[M_RIGHT];

	// �ʱ��� ��ü �׸� �־��ֱ�
	_body[IDLE]->MakeTexture(IDB_BITMAP_IDLE1, 2);
	_body[M_LEFT]->MakeTexture(IDB_BITMAP_MLEFT1, 5);
	_body[M_RIGHT]->MakeTexture(IDB_BITMAP_MRIGHT1, 5);
	_body[FALL]->MakeTexture(IDB_BITMAP_FALL1, 4);
	_body[JUMP_R]->MakeTexture(IDB_BITMAP_RIGHTJUMP1, 8);
	_body[JUMP_L]->MakeTexture(IDB_BITMAP_LEFTJUMP1, 8);
	_body[CLIMP]->MakeTexture(IDB_BITMAP_CLIMB1, 2);

	// �ʱ��� ó�� ��ġ ����
	for (auto &body : _body)
		body.second->UpdateAnimeCoord(_pos.x, _pos.y);

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
	// ������ �������� �ʱ��� ��ġ�� partMgr���� �˷��ֱ�
	InGamePart::_partsManager->SetNGRPosition(_pos);
}

void Neoguri::Draw()
{
	switch (state)
	{
	case Neoguri::M_LEFT:
		_body[M_LEFT]->DrawAnime(true);
		break;
	case Neoguri::M_RIGHT:
		_body[M_RIGHT]->DrawAnime(true);
		break;
	case Neoguri::S_LEFT:
		_body[S_LEFT]->DrawAnime(false);
		break;
	case Neoguri::S_RIGHT:
		_body[S_RIGHT]->DrawAnime(false);
		break;
	case Neoguri::JUMP:
		break;
	case Neoguri::CLIMP:
		break;
	case Neoguri::IDLE:
		_body[IDLE]->DrawAnime(false);
		break;
	case Neoguri::FALL:
		break;
	case Neoguri::DIE:
		break;
	}
}

void Neoguri::KeepPosInside()
{
	if (_pos.x < 0)				_pos.x = 0;
	if (_pos.y < 0)				_pos.y = 0;
	if (_pos.x > WindowWidth) 	_pos.x = WindowWidth;
	if (_pos.y > WindowHeight)	_pos.y = WindowHeight;
}

void Neoguri::UpdatePosition()
{

	int speed = 10;
	int keyFlag = key->CheckKey();

	// timeMgr���� ���� �ð��� �����ؼ� �����
	
	if (time->Alarm("NEOGURIMOVE",40,0))
	{
		static STATE justBefore = IDLE;
		if (state != JUMP)
		{
			justBefore = Move(justBefore);
		}
		else if (state == JUMP)
		{
			//justBefore = Jump(justBefore);
		}
		// ���� ������ ������ ������ ���ڸ� ������ �־���Ѵ�
		if (keyFlag & key->K_SPACE || state == JUMP) {

		}
		
		// ���� ���� ���ְų� ������ ���� ���ְų�
		if (justBefore == M_LEFT && keyFlag == 0)
			state = S_LEFT;
		if (justBefore == M_RIGHT && keyFlag == 0)
			state = S_RIGHT;
	}
	
	KeepPosInside();
}

void Neoguri::UpdateBodyAnime()
{
	_body[state]->UpdateAnimeCoord(_pos.x, _pos.y);
}
//
//Neoguri::STATE Neoguri::Jump(STATE justBefore)
//{
//	KeyMgr* key = KeyMgr::GetInstance();
//	int keyFlag = key->CheckKey();
//	TimeMgr* time = TimeMgr::GetInstance();
//	
//	switch (jump)
//	{
//		// ���� ����
//	case Neoguri::M_LEFT:
//		{
//			if (time->Alarm("AIRTIME", 50, 5) > 2) {
//				_pos.x -= 4;	_pos.y -= 4;
//			}
//			else if (time->Alarm("AIRTIME", 50, 5) > 2) {
//				_pos.x -= 4;	_pos.y += 6;
//			}
//			else if (time->Alarm("AIRTIME", 50, 5) == 0) {
//				return;
//			}
//			else if (time->Alarm("AIRTIME", 50, 5) == -1) {
//				state = S_LEFT;
//				return;
//			}
//		}	break;
//	// ������ ����
//	case Neoguri::M_RIGHT:
//		{
//			if (time->Alarm("AIRTIME", 50, 5) > 2) {
//				_pos.x += 4;	_pos.y -= 4;
//			}
//			else if (time->Alarm("AIRTIME", 50, 5) > 2) {
//				_pos.x += 4;	_pos.y += 6;
//			}
//			else if (time->Alarm("AIRTIME", 50, 5) == 0) {
//				return;
//			}
//			else if (time->Alarm("AIRTIME", 50, 5) == -1) {
//				state = S_RIGHT;
//				return;
//			}
//		}	break;
//	// �׳� ����
//	case Neoguri::IDLE:
//		{
//			if (time->Alarm("AIRTIME", 50, 4) > 2) {
//				_pos.y -= 4;
//			}
//			else if (time->Alarm("AIRTIME", 50, 4) > 0) {
//				_pos.y += 4;
//			}			
//			else if (time->Alarm("AIRTIME", 50, 4) == 0) {
//				return;
//			}
//			else if (time->Alarm("AIRTIME", 50, 4) == -1) {
//				state = S_LEFT;
//				return;
//			}
//		}	break;
//	}
//}

Neoguri::STATE Neoguri::Move(STATE justBefore)
{

	int speed = 10;
	int keyFlag = key->CheckKey();


	if (keyFlag & key->K_LEFT) {
		_pos.x -= speed;
		state = M_LEFT;
		return M_LEFT;
	}
	else if (keyFlag & key->K_RIGHT) {
		_pos.x += speed;
		state = M_RIGHT;
		return M_RIGHT;
	}
	else if (keyFlag & key->K_DOWN){
		bool radder = false;
		if (radder)//��ٸ��� �ִٸ�
		{
			_pos.y += speed;
			state = CLIMP;
			return IDLE;
		}
	}
	else if (keyFlag & key->K_UP){
		bool radder = false;
		if (radder)//��ٸ��� �ִٸ�
		{
			_pos.y += speed;
			state = CLIMP;
			return IDLE;
		}
	}
	else if (!keyFlag)
	{
		state = IDLE;
		return justBefore;
	}
}

Neoguri::STATE Neoguri::DiePhase()
{
	//�������� ��� �����
// �״� ���ϸ��̸� Ȱ��ȭ(���鼭 ������)
// ���� ��Һ��� y�� ����
	return STATE::FALL;

// �ٴڿ� ������ ����
	return STATE::DIE;
}

void Neoguri::WhatToOperateWithChainID(int id)
{
	state = DIE;
}
