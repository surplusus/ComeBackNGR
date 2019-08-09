#include "stdafx.h"
#include "Prey.h"
#include "Basic_Value.h"
#include "Animator.h"
using std::string;
using std::stringstream;
// 먹이 크기는 가로 42, 세로 42
std::vector<Prey*> Prey::PreyMemberPtr = std::vector<Prey*>(0);

Prey::Prey(PartsMgr *mgr,string n, int flr, int coordX, int order) 
	: InGamePart(mgr,coordX,flr), numOfOrder(order), name(n)
{
	pos = { coordX, flr };
	RECT co = { 0,0,40,40 };
	collider.UpdateCollider(co);
	collider.UpdateCollider(pos);
#ifdef _DEBUG
	RECT re = collider.GetColliderRect();
	std::cout << re.left << "  " << re.top << "  " << re.right<< "  " << re.bottom << std::endl;
#endif // _DEBUG

	Prey::PreyMemberPtr.push_back(this);

	// draw를 위한 포석
	score = new Animator(name,IDB_BITMAP_PREY_SCORE1, 5);
	score->SetAnimeSize(42, 42);
	// 중앙점과 그리는 점은 다름 (중하단 : pos) (좌상단 : 그리기 기준점)
	score->UpdateAnimeCoord(pos.x - 20, pos.y - 40);
	body = (HBITMAP)LoadImage(NULL,L"image/prey/prey1.bmp", IMAGE_BITMAP
		,0 ,0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	hdc = CreateCompatibleDC(g_hmemdc);
}

void Prey::Update()
{
	if (collider.OnNGRCollisionEnter())
		isRemoving = true;
	
	Prey* p = this;
	if (isRemoving)
	{
		NotyfyEventCall([p]() {p->RemovePreyProcedure(); });
		if (score->IsOneTickOver())
			EventBus::GetInstance()->Publish(new EventPreyRemove(std::shared_ptr<Prey>(this)));
		return;
	}

	numOfRemainedPrey = PreyMemberPtr.size();
	
	if (numOfRemainedPrey == 0 && isRemoving == false)
	{
		Notify(EVENTTYPE::NOPRAYLEFT);
		return;
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
		score->DrawAnime(true, 500);
	}
	else
	{
		SelectObject(hdc, body);
		TransparentBlt(g_hmemdc, pos.x - 21, pos.y - 42, 42, 42
			, hdc, 0, 0, 42, 42, RGB(0, 0, 0));
	}
}

bool Prey::CheckPreysRemain()
{
	for (auto p : Prey::PreyMemberPtr)
		if (p != nullptr)
			return true;

	return false;
}

bool Prey::RemovePreyProcedure()
{
	if (score->IsOneTickOver())
	{
		isRemoving = false;
		return true;
	}
	
	std::cout << "이벤트 잘되는가 실험중" << std::endl;
	return false;
}
