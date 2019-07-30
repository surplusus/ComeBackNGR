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
	
	R->TakeOn(this, &Opening::Draw);

	if (key->CheckKey() & key->K_SPACE)
	{
		SceneMgr* s = SceneMgr::GetInstance();
		s->MoveToNextScene();
	}
}

Opening::~Opening()
{
	HBITMAP oldbit = (HBITMAP)SelectObject(g_hmemdc, _imageBG);

	DeleteObject(_imageBG);
	DeleteObject(oldbit);
}

void Opening::DrawBG()
{
	if (!_imageBG)
	{
		MessageBox(g_hwnd, L"이미지 로드 실패", L"image/openingimage.bmp 파일이 없습니다", MB_OK);
		exit(0);
	}
	SelectObject(g_hmemdc, _imageBG);
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

	R->TakeOn(this, &Ending::Draw);

	if (key->CheckKey() & key->K_SPACE)
	{
		SceneMgr* s = SceneMgr::GetInstance();
		s->MoveToNextScene();
	}
}
