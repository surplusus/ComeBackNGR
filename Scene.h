#pragma once

class Scene
{
private:	//State pattern�� ���� ����
	friend class SceneMgr;
protected:	// scene���� �� ���� �� ������ ȣ��������
	void ChangeState(SceneMgr*,Scene*);
protected:
	virtual void Init() = 0;	// render���� �޹�� �ٲٱ�(SelectBackGroundScene)
	virtual void Update() = 0;
	virtual void Draw() {}	// call in renderer
};

class Opening : public Scene
{
public:
	virtual ~Opening();
private:
	//HBITMAP _imageBG;
	void DrawBG();
	void MoveEyes();
public:
	virtual void Init();
	virtual void Draw() override;
	virtual void Update();
};

class Ending : public Scene
{
	virtual void Init();
	virtual void Draw() override;
	virtual void Update();
};

