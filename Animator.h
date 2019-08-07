#pragma once
class TextureHandler;

class Animator
{
public:
	Animator(int idImage = 0, int countImageNum = 0);
	Animator(std::string, int);
	~Animator() {}
private:
	TextureHandler* _texture = nullptr;
	POINT _coord = { 0,0 };
	int animatorSpeedStandard = 0;
public:
	void UpdateAnimeCoord(int x, int y);
	const bool IsOneTickOver() const;
	void DrawAnime(bool isMoving, int speed);
	void SetAnimeSize(int cx, int cy);
};
