#include "stdafx.h"
#include "Neoguri.h"
#include "Basic_Value.h"
#include "Animator.h"
using std::cout;
using std::endl;
Neoguri::Neoguri(PartsMgr *mgr) : InGamePart(mgr, 710, FirstFloor - 24)
{
	// 너구리만의 층별 좌표
	floorList.push_back(FirstFloor - 20);
	floorList.push_back(SecondFloor - 20);
	floorList.push_back(ThirdFloor - 20);
	floorList.push_back(FourthFloor - 20);
	floorList.push_back(FifthFloor - 20);
	numOfFloorOn = floorList[0];
	// boundary 설정
	boundary[0] = { 50,90,670,510 };
	boundary[1] = { 665,440,745,515 };
	// 몸체 애니메이터 만들기
	_body[IDLE] = new Animator("NEOGURI",IDB_BITMAP_IDLE1, 6);
	_body[M_LEFT] = new Animator("NEOGURI", IDB_BITMAP_MLEFT1, 5);
	_body[M_RIGHT] = new Animator("NEOGURI", IDB_BITMAP_MRIGHT1, 5);
	_body[FALL] = new Animator("NEOGURI", IDB_BITMAP_FALL1, 4);
	_body[JUMP_R] = new Animator("NEOGURI", IDB_BITMAP_RIGHTJUMP1, 8);
	_body[JUMP_L] = new Animator("NEOGURI", IDB_BITMAP_LEFTJUMP1, 8);
	_body[CLIMB] = new Animator("NEOGURI", IDB_BITMAP_CLIMB1, 2);
	_body[S_LEFT] = _body[M_LEFT];
	_body[S_RIGHT] = _body[M_RIGHT];
	_body[DIE] = _body[FALL];
	_body[JUMP_I] = _body[IDLE];

	// 너구리 몸체 (좌상단 : 그리기 기준점)
	// 중앙점과 그리는 점은 다름 (중단 : pos) // 먹이와 몬스터와 다르게 collider없음 주의
	for (auto &body : _body)
		body.second->UpdateAnimeCoord(pos.x - 21, pos.y - 24);

	// EventBus

}

void Neoguri::Update()
{
	if (!(state == FALL || state == DIE))
	{
		UpdatePosition();
		// 중앙점과 그리는 점은 다름 (중하단 : pos) (좌상단 : 그리기 기준점)
		_body[state]->UpdateAnimeCoord(pos.x - 21, pos.y - 24);
	}
	else
	{
		DiePhase();
	}
	// 할일이 끝났으면 너구리 위치를 partMgr에게 알려주기
	InGamePart::_partsManager->SetNGRPosition(pos);
}

void Neoguri::Draw()
{
	switch (state)
	{
	case Neoguri::M_LEFT:
		_body[M_LEFT]->	DrawAnime(true,480);
		break;
	case Neoguri::M_RIGHT:
		_body[M_RIGHT]->DrawAnime(true, 480);
		break;
	case Neoguri::S_LEFT:
		_body[S_LEFT]->	DrawAnime(false, 0);
		break;
	case Neoguri::S_RIGHT:
		_body[S_RIGHT]->DrawAnime(false, 0);
		break;
	case Neoguri::JUMP_I:
		_body[IDLE]->	DrawAnime(true, 80);
		break;
	case Neoguri::JUMP_R:
		_body[JUMP_R]->	DrawAnime(true, 80);
		break;
	case Neoguri::JUMP_L:
		_body[JUMP_L]->	DrawAnime(true, 80);
		break;
	case Neoguri::CLIMB:
		_body[CLIMB]->	DrawAnime((isGoingUp || isGoingDown), 60);
		break;
	case Neoguri::IDLE:
		_body[IDLE]->DrawAnime(false, 0);
		break;
	case Neoguri::FALL:
		_body[FALL]->DrawAnime(true, 360);
		break;
	case Neoguri::DIE:
		_body[DIE]->DrawAnime(false, 0);
		break;
	default:
		break;
	}

}

void Neoguri::KeepPosInside()
{
	if (numOfFloorOn == floorList[0])	{
		if (pos.x < 65)		pos.x = 66;
		if (pos.x > 720)	pos.x = 719;
	}
	else	{
		if (pos.x < 65)		pos.x = 66;
		if (pos.x > 655)	pos.x = 653;
	}
}
#include "Logger.h"
void Neoguri::UpdatePosition()
{
	if (state == FALL || state == DIE)
		return;

	int speed = 10;
	int keyFlag = key->CheckKey();
	
	if (timer->Alarm("NEOGURIMOVE",48,0))
	{
		static STATE justBefore = IDLE;

		// 왼쪽 점프와 오른쪽 점프와 제자리 점프가 있어야한다
		if (isGoingUp == false && isGoingDown == false)
		{
			if ((keyFlag & key->K_SPACE))
			{
				isGoingUp = true;
				if (justBefore == M_LEFT || justBefore == S_LEFT)
					state = JUMP_L;
				else if (justBefore == M_RIGHT || justBefore == S_RIGHT)
					state = JUMP_R;
				else if (justBefore == IDLE)
					state = JUMP_I;
				else
					cout << "그럼 어떻게 들어왔냐?" << endl;
				Notify(AIRTIME);
			}
		}
		
		if (state == JUMP_L || state == JUMP_R || state == JUMP_I) {
			Jump(justBefore, isGoingUp, isGoingDown);
		}
		else
		{
			if (isOnLadder)
			{
				if (keyFlag & key->K_UP) {
					isGoingUp = true;
					state = CLIMB;
				}
				else if (keyFlag & key->K_DOWN) {
					isGoingDown = true;
					state = CLIMB;
				}
				else
					isGoingUp = isGoingDown = false;
			}
			
			if(state == CLIMB)
				justBefore = MoveUD(justBefore);
			else
				justBefore = MoveLR(justBefore);
		}
	}
	KeepPosInside();
}

Neoguri::STATE Neoguri::Jump(STATE justBefore, bool& goUp, bool& goDown)
{
	int jumpheight;
	int changeRateX;
	int changeRateY;
	STATE returnstate = justBefore;
	
	// 점프 타입마다 switch문
	switch (state)
	{
		// 왼쪽 점프
		case Neoguri::JUMP_L :
		{
			// 작은 점프
			if (justBefore == S_LEFT)
			{
				jumpheight = 25;
				changeRateX = -5;
				changeRateY = -5;
			}
			// 높은 점프
			if (justBefore == M_LEFT)
			{
				jumpheight = 35;
				changeRateX = -7;
				changeRateY = -5;
			}
			
		}	break;
		// 오른쪽 점프
		case Neoguri::JUMP_R:
		{
			// 작은 점프
			if (justBefore == S_RIGHT)
			{
				jumpheight = 25;
				changeRateX = +5;
				changeRateY = -5;
			}
			// 높은 점프
			if (justBefore == M_RIGHT)
			{
				jumpheight = 35;
				changeRateX = +7;
				changeRateY = -5;
			}

		}	break;
		// 제자리 점프
		case Neoguri::JUMP_I:
		{
			// 작은 점프
			if (justBefore == IDLE)
			{
				jumpheight = 25;
				changeRateX = 0;
				changeRateY = -5;
			}
			
		}	break;
	}
	// 정점에 다다르면 올라가는건 false 내려가는건 true
	if (pos.y <= InGamePart::numOfFloorOn - jumpheight)
	{
		isGoingUp = false;
		isGoingDown = true;
	}
	// 너구리 위치를 바꾸는 알고리즘
	pos.x += changeRateX;
	if (isGoingUp) {
		pos.y += changeRateY;
	}
	else if(isGoingDown)
	{
		//떨어지고 있는 도중 판단
		pos.y -= changeRateY;
		// 땅에 도착했는지 판단
		if (pos.y >= numOfFloorOn)
		{
			justBefore = state;
			pos.y = numOfFloorOn;
			isGoingDown = false;
			_body[state]->ResetAnimeImageOrder();
			// 점프 입력이 처음 들어왔을때
			if (justBefore == JUMP_I)		state = IDLE;
			else if (justBefore == JUMP_L)  state = S_LEFT;
			else if (justBefore == JUMP_R)  state = S_RIGHT;
			Notify(LAND);
		}
	}
	else
		cout << "여기있으면 안되는뎀...이미 다떨어졌는데" << endl;

	return justBefore;
}

int Neoguri::ChangeNumOfFloorOn()
{
	std::vector<int> v;
	v.push_back(static_cast<int>(abs(FirstFloor - pos.y)));
	v.push_back(static_cast<int>(abs(SecondFloor - pos.y)));
	v.push_back(static_cast<int>(abs(ThirdFloor - pos.y)));
	v.push_back(static_cast<int>(abs(FourthFloor - pos.y)));
	v.push_back(static_cast<int>(abs(FifthFloor - pos.y)));
	int min = 999;
	int result = 0;
	for (int i = 0; i < v.size(); ++i)
	{
		if (min > v[i]) {
			min = v[i];
			result = floorList[i];
		}
	}
	return result;
}

Neoguri::STATE Neoguri::MoveLR(STATE justBefore)
{

	int speed = 10;
	int keyFlag = key->CheckKey();

	if (keyFlag & key->K_LEFT) {
		pos.x -= speed;
		state = M_LEFT;
	}
	else if (keyFlag & key->K_RIGHT) {
		pos.x += speed;
		state = M_RIGHT;
	}
	else if (!keyFlag)
	{
		if (justBefore == M_RIGHT)
			state = S_RIGHT;
		else if (justBefore == M_LEFT)
			state = S_LEFT;
		else
			state = justBefore;
	}
		return state;
}

Neoguri::STATE Neoguri::MoveUD(STATE justbefore)
{
	int keyFlag = key->CheckKey();
	int speed = 10;

	if (keyFlag & key->K_DOWN) {
		if (pos.y < floorList[0])
		{
			pos.y += speed;
			state = CLIMB;
		}
	}
	else if (keyFlag & key->K_UP) {
		if (pos.y > floorList[4]) {
			pos.y -= speed;
			state = CLIMB;
		}
	}

	// 여러 층을 만들어야됨
	if (state == CLIMB)
	{
		// 위로 올라갈때
		if (InGamePart::numOfFloorOn - pos.y >=90)
		{
			InGamePart::numOfFloorOn = ChangeNumOfFloorOn();
			isOnLadder = false;
			pos.y = numOfFloorOn;
			state = IDLE;
			isGoingUp = isGoingDown = false;
		}
	}
	return justbefore;
}

Neoguri::STATE Neoguri::DiePhase()
{
	if (timer->Alarm("NEOGURIFALL", 100, 30))
	{ 
		if (pos.y < FirstFloor - 42)
		{
			pos.y += 10;
			_body[FALL]->UpdateAnimeCoord(pos.x - 21, pos.y - 24);
			return STATE::FALL;
		}
		else
		{
			state = DIE;
			_body[DIE]->UpdateAnimeCoord(pos.x - 21, pos.y - 24);
			Notify(EVENTTYPE::DIE);
			return STATE::DIE;
		}
	}
	return STATE::FALL;
}

bool Neoguri::ToggleLadderState()
{
	// 옵저버에서 계속 부를 동안은 
	// 한번만 켜진다.
	if (state != CLIMB && isOnLadder == false)
		return isOnLadder = true;
	
	return isOnLadder;
}

void Neoguri::Restart()
{
	pos.x = 710;
	pos.y = FirstFloor - 24;
	for (auto &body : _body)
		body.second->UpdateAnimeCoord(pos.x - 21, pos.y - 24);
	collider.UpdateCollider(pos);
	state = IDLE;
}

void Neoguri::Die()
{
	state = FALL;
}
