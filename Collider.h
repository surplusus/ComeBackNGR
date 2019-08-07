#pragma once

typedef struct _tagCollider
{
	POINT _checkPos;
	int _posX;
	int _posY;
	int _cx;
	int _cy;
	RECT _rect;
} STRCT_COL;

class PartsMgr;

class Collider
{
public:
	Collider(PartsMgr* p) : _parts(p) {}
	virtual ~Collider() = default;
private:
	STRCT_COL col;
	PartsMgr* _parts;
public:
	void UpdateCollider(POINT checkpos);
	void UpdateCollider(int x1, int y1, int x2, int y2);
	void UpdateCollider(RECT re);

	bool OnNGRCollisionEnter();
	// 디버깅용 박스 출력용
	const RECT& GetColliderRect() const { return col._rect; }
};



