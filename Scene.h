#pragma once
#include "Animator.h"

class Scene
{
private:	//State pattern�� ���� ����
	friend class SceneMgr;
protected:	// scene���� �� ���� �� ������ ȣ��������
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

