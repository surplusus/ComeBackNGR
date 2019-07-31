#pragma once
class TextureHandler;

class Animator
{
public:
	Animator() {}
	~Animator() {}
private:
	TextureHandler* _texture = nullptr;
	POINT _coord = { 0,0 };

public:
	enum {NEOGURI,MONSTER, OPENING,ENDING	};

	void UpdateAnimeCoord(int x, int y);
	void MakeTexture(int idImage, int countImageNum);

	void DrawAnime(bool isMoving);
};
