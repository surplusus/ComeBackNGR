#include "stdafx.h"
#include "Scene.h"

void Scene::ChangeState(SceneMgr *m, Scene *s)
{
	m->ChangeScene(s);
}

void Opening::Init()
{
}

void Opening::Draw()
{
	Renderer* R = Renderer::GetInstance();
	R->LoadBGImageFromFile((LPWSTR)_T("image/openingimage"));
	MoveEyes();
	Scene::func = static_cast<void (Scene::*)(void)>(Opening::Draw);
	R->ListUpDrawFunc(func);
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
