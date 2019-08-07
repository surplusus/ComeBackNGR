#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle(PartsMgr *mgr, int numOfFloorOn, int coordX) 
	: InGamePart(mgr)
{
	pos.x = coordX - 15;
	pos.y = numOfFloorOn;
	RECT re = { 0,0,5,5 };
	collider.UpdateCollider(re);
	collider.UpdateCollider(pos);
	_body = (HBITMAP)LoadBitmap(NULL, MAKEINTRESOURCE(IDB_BITMAP_PIN));
	_hdc = CreateCompatibleDC(g_hmemdc);
	SelectObject(_hdc, _body);
}

void Obstacle::Update()
{
	// ³Ê±¸¸®¶û ºÎµúÈ÷¸é Á×´Â ÀÌº¥Æ® ¹ß»ý
	if (collider.OnNGRCollisionEnter())
		Notify(OBSTACLE);
}

void Obstacle::Draw()
{
#ifdef _DEBUG
	RECT r = collider.GetColliderRect();
	Rectangle(_hdc, r.left, r.top, r.right, r.bottom);
#endif // _DEBUG
	BitBlt(g_hmemdc, pos.x, pos.y, 30, 30, _hdc, 0, 0, SRCCOPY);
}
