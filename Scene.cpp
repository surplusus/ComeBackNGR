#include "stdafx.h"
#include "Scene.h"

void Scene::ChangeState(SceneMgr *m, Scene *s)
{
	m->ChangeScene(s);
}

void Opening::Init()
{
	_imageBG = (HBITMAP)LoadImage(NULL, _T("image/openingimage.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void Opening::Draw()
{
	DrawBG();
	MoveEyes();
}

void Opening::Update()
{
	// �� ���ư��� �ִϸ��̼� ������Ʈ
	// ����κ�
	//Renderer::GetInstance()->AddListDrawFunc(func);
	Renderer* R = Renderer::GetInstance();
	
	R->TakeOn(this, &Opening::Draw);
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
		MessageBox(g_hwnd, L"�̹��� �ε� ����", L"image/openingimage.bmp ������ �����ϴ�", MB_OK);
		exit(0);
	}
	SelectObject(g_hmemdc, _imageBG);
}

void Opening::MoveEyes()
{
	HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH old = (HBRUSH)SelectObject(g_hmemdc, blackBrush);
	
	TimeMgr* time = TimeMgr::GetInstance();
	int eyeSize = 30;
	time->SetPeriod(TimeMgr::EYEMOVE);
	int speed = time->DeltaTime(TimeMgr::EYEMOVE) / 300;
	
	Ellipse(g_hmemdc, 100 + speed, 100, 100 + eyeSize + speed, 100 + eyeSize);

	SelectObject(g_hmemdc, (HBRUSH)old);
	DeleteObject((HBRUSH)blackBrush);
}

void Ending::Init()
{
}

void Ending::Draw()
{
	//Renderer::GetInstance()->LoadBGImageFromFile("image/endingimage");

}
