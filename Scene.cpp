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
	_hdc = CreateCompatibleDC(g_hmemdc);
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
	TimeMgr* T = TimeMgr::GetInstance();

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
	
	int eyeSize = 12;
	POINT lefteye = { 530,400 };
	POINT righteye = { 620,380 };
	static int speed = 0;
	static bool eyeflag = true;
	if (time->Alarm("MOVEEYE",60,0))
	{
		if (eyeflag)
			speed += 4;
		else
			speed -= 4;

		if (speed < 0 || speed >50)
			eyeflag = !eyeflag;
	}
	Ellipse(g_hmemdc, lefteye.x + speed, lefteye.y, lefteye.x + eyeSize + speed, lefteye.y + eyeSize);
	Ellipse(g_hmemdc, righteye.x + speed, righteye.y, righteye.x + eyeSize + speed, righteye.y + eyeSize);


	SelectObject(_hdc, (HBRUSH)old);
	DeleteObject((HBRUSH)blackBrush);
}

void Ending::Init()
{
	Renderer* R = Renderer::GetInstance();
	R->SelectBackGroundScene(R->T_ENDING);

	_dieBG = (HBITMAP)LoadImage(NULL, L"image/ending/die.bmp"
		, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	_hdc = CreateCompatibleDC(g_hmemdc);
}

void Ending::Draw()
{
	switch (state)
	{
	case Ending::NGRDIE:
	{
		SelectObject(_hdc, _dieBG);
		BitBlt(g_hmemdc, 0, 0, WindowWidth, WindowHeight, _hdc, 0, 0, SRCCOPY);
		break;
	}
	case Ending::BADEND:
		break;
	case Ending::HAPPYEND:
		break;
	default:
		break;
	}
}

void Ending::Update()
{
	Renderer* R = Renderer::GetInstance();
	KeyMgr* key = KeyMgr::GetInstance();

	if (key->CheckKey() & key->K_SPACE)
	{
		SceneMgr* s = SceneMgr::GetInstance();
		s->BackToInGameScene();
	}
	if (key->CheckKey() & key->K_ESC)
	{
		DestroyWindow(g_hwnd);
	}
}
