#pragma once

class Scene
{
private:	//State pattern을 한 포석
	friend class SceneMgr;
protected:	// scene에서 할 일이 다 끝나면 호출해주자
	void ChangeState(SceneMgr*,Scene*);
protected:
	virtual void Draw(HDC) = 0;
};

class Opening : public Scene
{
	virtual void Draw(HDC);
};

class Ending : public Scene
{
	virtual void Draw(HDC);
};

