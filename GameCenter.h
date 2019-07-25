#pragma once
class Scene;

class GameCenter
{
private:
	GameCenter() {}
	GameCenter(GameCenter&) {}
	~GameCenter(){}
private:
	static GameCenter* instance;
public:
	static GameCenter* GetInstance();
	static void Release();
private:	//State pattern�� ���� ����
	friend class Scene;
	Scene* _scene;
	void ChangeScene(Scene*);
public:
	void Init();
};