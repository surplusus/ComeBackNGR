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
	HDC _hdc;

	void DrawBG();
	void MoveEyes();
public:
	virtual void Init();
	virtual void Draw() override;
	virtual void Update();
};

class Ending : public Scene
{
	enum S_STATE	{
		NGRDIE, BADEND, HAPPYEND,
	};
public:
	virtual void Init();
	virtual void Draw() override;
	virtual void Update();
private:
	S_STATE state = NGRDIE;
	HBITMAP _dieBG;
	HBITMAP _happyBG;
	HDC _hdc;
};

