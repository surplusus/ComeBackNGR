#pragma once

class Scene
{
private:	//State pattern을 위한 포석
	friend class SceneMgr;
protected:	// scene에서 할 일이 다 끝나면 호출해주자
	void ChangeState(SceneMgr*,Scene*);
protected:
	virtual void Init() = 0;	// render에서 뒷배경 바꾸기(SelectBackGroundScene)
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

