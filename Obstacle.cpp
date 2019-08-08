#include "stdafx.h"
#include "Obstacle.h"
#include "Basic_Value.h"

Obstacle::Obstacle(PartsMgr *mgr, int numOfFloorOn, int coordX) 
	: InGamePart(mgr)
{
	pos.x = coordX;
	pos.y = numOfFloorOn + 3;
	RECT re = { 0,0,10,20 };
	collider.UpdateCollider(re);
	collider.UpdateCollider(pos);
	_body = (HBITMAP)LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP_PIN));
	_hdc = CreateCompatibleDC(g_hmemdc);
}

void Obstacle::Update()
{
	// ³Ê±¸¸®¶û ºÎµúÈ÷¸é Á×´Â ÀÌº¥Æ® ¹ß»ý
	if (collider.OnNGRCollisionEnter())
		Notify(OBSTACLE);
}

void Obstacle::Draw()
{

//#ifdef _DEBUG
//	RECT r = collider.GetColliderRect();
//	FillRect(g_hmemdc, &r, (HBRUSH)GetStockObject(GRAY_BRUSH));
//#endif // _DEBUG
	SelectObject(_hdc, _body);
	TransparentBlt(g_hmemdc, pos.x - 15, pos.y - 30, 30, 30
		, _hdc, 0, 0, 30, 30, RGB(0, 0, 0));
}
