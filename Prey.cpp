#include "stdafx.h"
#include "Prey.h"
#include "Basic_Value.h"
#include "Animator.h"
using std::string;
using std::stringstream;
// 먹이 크기는 가로 42, 세로 42
std::vector<Prey*> Prey::PreyMemberPtr = std::vector<Prey*>(0);

Prey::Prey(PartsMgr *mgr, int flr, int coordX, int order) 
	: InGamePart(mgr,coordX,flr), numOfOrder(order)
{
	pos = { coordX, flr };
	collider.UpdateCollider(coordX + 10, flr + 20, coordX + 20, flr);
	std::cout << coordX - 10 << "  " << flr + 20 << "  " << coordX + 10 << "  " << flr << std::endl;
	Prey::PreyMemberPtr.push_back(this);

	// draw를 위한 포석
	score = new Animator(IDB_BITMAP_PREY_SCORE1, 5);
	score->SetAnimeSize(42, 42);
	body = (HBITMAP)LoadImage(NULL,L"image/prey/prey3.bmp", IMAGE_BITMAP
		,0 ,0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	hdc = CreateCompatibleDC(g_hmemdc);
}

void Prey::Update()
{
	if (isRemoving)
		isRemoving++;
	if (isRemoving >= 1600)
		return;

	if (!CheckPreysRemain())
	{
		Notify(EVENTTYPE::NEXTSTAGE);
		return;
	}

	if (collider.OnNGRCollisionEnter() && (isRemoving == 0))
	{
		Notify(EVENTTYPE::PRAY);
		body = (HBITMAP)LoadBitmap(NULL, MAKEINTRESOURCE(IDB_BITMAP_PREY_SCORE1));
		isRemoving = 1;
	}
	
}

void Prey::Draw()
{
	if (body == NULL)
	{
		std::cout << "먹이 body HBITMAP이 NULL 입니다." << std::endl;
		exit(0);
	}

	if (isRemoving)
	{
		score->DrawAnime(true, 100);
	}
	else
	{
		SelectObject(hdc, body);
		TransparentBlt(g_hmemdc, pos.x, pos.y, 42, 42
			, hdc, 0, 0, 42, 42, RGB(0, 0, 0));
	}
#ifdef _DEBUG
	static bool flag = false;
	if (!flag) {
		std::cout << "먹이 그리기" << std::endl;
		flag = true;
	}
#endif // _DEBUG
}

bool Prey::CheckPreysRemain()
{
	for (auto p : Prey::PreyMemberPtr)
		if (p != nullptr)
			return true;

	return false;
}

void Prey::RemovePreyProcedure()
{
	
	score->DrawAnime(true, 100);
}
