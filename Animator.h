#pragma once
#include <Windows.h>
#include "Texture.h"
#include "resource.h"

class Animator
{
public:
	Animator() {}
	~Animator() { _texture.ReleaseImage(); }
private:
	TEXTURE _texture;
public:
	enum {NEOGURI,MONSTER, OPENING,ENDING	};

	void UpdateAnimeCoord(int, int);
	void MakeTexture(int id, int numSize);
	HBITMAP GetAnimeHBITMAP() { return _texture._bit; }
};

void Animator::UpdateAnimeCoord(int x, int y)
{
	// timeMgr���� ���� �ð��� �����ؼ� �ٽø����
#ifdef _DEBUG
	static int nowtime = 0;
	nowtime++;
#endif // _DEBUG
	int imageCutSize = _texture._images.size();
	_texture._bit = _texture._images[nowtime / 100000 % imageCutSize];
}

inline void Animator::MakeTexture(int id, int numSize)
{
	if (id == NEOGURI)
		_texture.MakeTexture(IDB_BITMAP1, numSize);
	else if (id == MONSTER)
		_texture.MakeTexture(IDB_BITMAP_M1, numSize);
}
