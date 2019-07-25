#include "stdafx.h"
#include "Scene.h"

void Scene::ChangeState(SceneMgr *m, Scene *s)
{
	m->ChangeScene(s);
}
