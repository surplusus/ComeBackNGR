#pragma once
#include "Animator.h"

class Scene
{
private:	//State pattern을 위한 포석
	friend class SceneMgr;
protected:	// scene에서 할 일이 다 끝나면 호출해주자
	void ChangeState(SceneMgr*,Scene*);
	void(Scene::*func)(void);
protected:
	virtual void Init() = 0;
	virtual void Draw() = 0;
};

class Opening : public Scene
{
public:
public:
	virtual void Init();
	virtual void Draw();
	void MoveEyes();
};

class Ending : public Scene
{
	virtual void Init();
	virtual void Draw();
};

