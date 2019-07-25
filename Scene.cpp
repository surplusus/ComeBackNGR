#include "stdafx.h"
#include "Scene.h"

void Scene::ChangeState(GameCenter *g, Scene *s)
{
	g->ChangeScene(s);
}
