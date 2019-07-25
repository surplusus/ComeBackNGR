#pragma once
class Scene;
class KeyMgr;
class SceneMgr;
class Renderer;
class TimeMgr;

class GameCenter
{
public:
	GameCenter();
	~GameCenter();
private:
	KeyMgr* _key;
	SceneMgr* _scene;
	Renderer* _render;
	TimeMgr* _time;
public:
	void Init();
	void OperateProcedure();
	void Render();

};