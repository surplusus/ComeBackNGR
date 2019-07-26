#include "stdafx.h"
#include "Scene.h"

void Scene::ChangeState(SceneMgr *m, Scene *s)
{
	m->ChangeScene(s);
}

void Opening::Draw(HDC)
{
	Renderer::GetInstance()->LoadBGImageFromFile("image/openingimage");
}

void Opening::MoveEyes(HDC hdc)
{
	
}

void Ending::Draw(HDC)
{
	Renderer::GetInstance()->LoadBGImageFromFile("image/endingimage");
}
