#pragma once

class Scene
{
private:	//State pattern�� �� ����
	friend class SceneMgr;
protected:	// scene���� �� ���� �� ������ ȣ��������
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

