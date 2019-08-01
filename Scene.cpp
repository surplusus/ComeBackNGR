#include "stdafx.h"
#include "Scene.h"
#include "Basic_Value.h"

void Scene::ChangeState(SceneMgr *mgr, Scene *s)
{
	mgr->ChangeScene(s);
}

void Opening::Init()
{
	// HBITMAP을 scene이 가지고 있을 경우
	//_imageBG = (HBITMAP)LoadImage(NULL, _T("image/openingimage.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	Renderer* R = Renderer::GetInstance();

	R->SelectBackGroundScene(R->T_OPENING);
}

void Opening::Draw()
{
	DrawBG();
	MoveEyes();
}

void Opening::Update()
{
	Renderer* R = Renderer::GetInstance();
	KeyMgr* key = KeyMgr::GetInstance();
	
	//R->drawbus->TakeOn<Opening>(this, &Opening::Draw); //보류

	if (key->CheckKey() & key->K_SPACE)
	{
		SceneMgr* s = SceneMgr::GetInstance();
		s->MoveToNextScene();
	}
}

Opening::~Opening()
{
	//DeleteObject(_imageBG); // 뒷배경 이미지는 랜더가 들고있다
}

void Opening::DrawBG()
{
	Renderer* R = Renderer::GetInstance();
	
	R->SelectBackGroundScene(R->T_OPENING);
}

void Opening::MoveEyes()
{
	TimeMgr* time = TimeMgr::GetInstance();

	HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH old = (HBRUSH)SelectObject(g_hmemdc, blackBrush);
	
	int eyeSize = 30;
	time->SetPeriod(TimeMgr::EYEMOVE);
	int speed = time->DeltaTime(TimeMgr::EYEMOVE) / 300;
	
	Ellipse(g_hmemdc, 100 + speed, 100, 100 + eyeSize + speed, 100 + eyeSize);

	SelectObject(g_hmemdc, (HBRUSH)old);
	DeleteObject((HBRUSH)blackBrush);
}

void Ending::Init()
{
	Renderer* R = Renderer::GetInstance();

	R->SelectBackGroundScene(R->T_ENDING);
}

void Ending::Draw()
{
	
}

void Ending::Update()
{
	Renderer* R = Renderer::GetInstance();
	KeyMgr* key = KeyMgr::GetInstance();

	//R->drawbus->TakeOn<Ending>(this, &Ending::Draw);	// 보류

	if (key->CheckKey() & key->K_SPACE)
	{
		SceneMgr* s = SceneMgr::GetInstance();
		s->MoveToNextScene();
	}
}
