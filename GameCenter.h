#pragma once
class Scene;
class KeyMgr;
class SceneMgr;
class Renderer;
class TimeMgr;
class SoundMgr;

class GameCenter
{
public:
	GameCenter();
	~GameCenter() {}
private:
	KeyMgr* _key;
	SceneMgr* _scene;
	Renderer* _render;
	TimeMgr* _time;
	SoundMgr* _sound;
public:
	void InitAll();
	void OperateProcedure();
	void ReleaseProcedure();
};