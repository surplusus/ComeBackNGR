#include "stdafx.h"
#include "Neoguri.h"
#include "Basic_Value.h"
#include "Animator.h"

Neoguri::Neoguri(PartsMgr *mgr) : InGamePart(mgr)
{
	_body = new Animator;
	// �ʱ��� ��ü �׸� �־��ֱ�
	_body->MakeTexture(IDB_BITMAP3, 7);
	// �ʱ��� ó�� ��ġ ����
	_body->UpdateAnimeCoord(700, 465);

	TimeMgr* time = TimeMgr::GetInstance();
	time->SetPeriod("NEOGURI");
}

void Neoguri::Update()
{
	UpdatePosition();
	UpdateBodyAnime();
}

void Neoguri::Draw()
{
	if (state == IDLE)
		_body->DrawAnime(false);
	if (state == M_LEFT)
		_body->DrawAnime(true);
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
	KeyMgr* key = KeyMgr::GetInstance();
	TimeMgr* time = TimeMgr::GetInstance();

	int speed = 10;
	int keyFlag = key->CheckKey();

	// timeMgr���� ���� �ð��� �����ؼ� �����
	if (time->DeltaTime("EYEMOVE") % 1000 == 0)
	{
		Sleep(10);
		static STATE justBefore = IDLE;
		if (state != JUMP)
		{
			if (keyFlag & key->K_LEFT) {
				_pos.x -= speed;
				state = M_LEFT;
				justBefore = M_LEFT;
			}
			else if (keyFlag & key->K_RIGHT) {
				_pos.x += speed;
				state = M_RIGHT;
				justBefore = M_RIGHT;
			}
			else {
				state = IDLE;
			}
		}
		
		// ���� ������ ������ ������ ���ڸ� ������ �־���Ѵ�
		if (keyFlag & key->K_SPACE || state == JUMP) {
			Jump(justBefore);
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
	_body->UpdateAnimeCoord(_pos.x, _pos.y);

}

void Neoguri::Jump(STATE jump)
{
	KeyMgr* key = KeyMgr::GetInstance();
	int keyFlag = key->CheckKey();
	TimeMgr* time = TimeMgr::GetInstance();
	
	switch (jump)
	{
		// ���� ����
	case Neoguri::M_LEFT:
		{
			if (time->Alarm("AIRTIME", 50, 5) > 2) {
				_pos.x -= 4;	_pos.y -= 4;
			}
			else if (time->Alarm("AIRTIME", 50, 5) > 2) {
				_pos.x -= 4;	_pos.y += 6;
			}
			else if (time->Alarm("AIRTIME", 50, 5) == 0) {
				return;
			}
			else if (time->Alarm("AIRTIME", 50, 5) == -1) {
				state = S_LEFT;
				return;
			}
		}	break;
	// ������ ����
	case Neoguri::M_RIGHT:
		{
			if (time->Alarm("AIRTIME", 50, 5) > 2) {
				_pos.x += 4;	_pos.y -= 4;
			}
			else if (time->Alarm("AIRTIME", 50, 5) > 2) {
				_pos.x += 4;	_pos.y += 6;
			}
			else if (time->Alarm("AIRTIME", 50, 5) == 0) {
				return;
			}
			else if (time->Alarm("AIRTIME", 50, 5) == -1) {
				state = S_RIGHT;
				return;
			}
		}	break;
	// �׳� ����
	case Neoguri::IDLE:
		{
			if (time->Alarm("AIRTIME", 50, 4) > 2) {
				_pos.y -= 4;
			}
			else if (time->Alarm("AIRTIME", 50, 4) > 0) {
				_pos.y += 4;
			}			
			else if (time->Alarm("AIRTIME", 50, 4) == 0) {
				return;
			}
			else if (time->Alarm("AIRTIME", 50, 4) == -1) {
				state = S_LEFT;
				return;
			}
		}	break;
	}
}
