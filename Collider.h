#pragma once

typedef struct _tagCollider
{
	POINT _pos;
	int _posX;
	int _posY;
	int _cx;
	int _cy;
	RECT _rect;
	_tagCollider(POINT pos1, POINT pos2);
	_tagCollider(int, int, int, int);
	_tagCollider(RECT);
} STRCT_COL;


class Collider
{
private:
	STRCT_COL col;
public:
	Collider();
	virtual ~Collider();
};

