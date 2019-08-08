#pragma once
class TextureHandler;

class Animator
{
public:
	Animator(std::string name, int idImage = 0, int countImageNum = 0);
	Animator(std::string name, std::string, int);
	~Animator() {}
private:
	std::string timeName;
	TimeMgr* timer = TimeMgr::GetInstance();
	int deltaTime;
	TextureHandler* _texture = nullptr;
	POINT _coord = { 0,0 };
	int animatorSpeedStandard = 1600;
public:
	void UpdateAnimeCoord(int x, int y);
	const bool IsOneTickOver() const;
	void DrawAnime(bool isMoving, int speed);
	void SetAnimeSize(int cx, int cy);
	int GetTextureImageNum();
	void ResetAnimeImageOrder();
};
