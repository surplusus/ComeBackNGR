#include "stdafx.h"
#include "Neoguri.h"
#include "Basic_Value.h"
#include "Animator.h"

Neoguri::Neoguri(PartsMgr *mgr) : InGamePart(mgr)
{
	_body = new Animator;
	// 너구리 몸체 그림 넣어주기
	_body->MakeTexture(IDB_BITMAP3, 7);
	// 너구리 처음 위치 설정
	_body->UpdateAnimeCoord(200, 200);

	TimeMgr* time = TimeMgr::GetInstance();
	time->SetPeriod(time->NEOGURI);
}

void Neoguri::Update()
{
	KeyMgr* key = KeyMgr::GetInstance();
	Renderer* R = Renderer::GetInstance();
	TimeMgr* time = TimeMgr::GetInstance();

	int speed = 10;
	int keyFlag = key->CheckKey();

	// timeMgr에서 시작 시간을 참고해서 만들기
	if (time->Alarm(time->NEOGURI, 1000))
	{
	if (keyFlag & key->K_LEFT)
		_body->UpdateAnimeCoord(-speed, 0);
	if (keyFlag & key->K_RIGHT)
		_body->UpdateAnimeCoord(speed, 0);

	}
	R->TakeOn(this, &Neoguri::Draw);
}

void Neoguri::Draw()
{


}
