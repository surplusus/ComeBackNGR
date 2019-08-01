#pragma once
class SceneMgr
{
private:
	static SceneMgr* instance;
	SceneMgr() {}
	~SceneMgr() {}
public:
	static SceneMgr* GetInstance();
	static void Release();
private:	//State pattern을 위한 포석
	friend class Scene;
	void ChangeScene(Scene*);
	Scene* _curScene;

	enum {OPEN = 0,GAME,END	};
	int _sceneNum;

public:
	std::vector<Scene*> v_Scenes;
	
	void Init();
	void Update();
	void MoveToNextScene();
	void DrawScene();
};

