#include "stdafx.h"
#include "Neoguri.h"
#include "Basic_Value.h"
#include "Animator.h"
using std::cout;
using std::endl;
Neoguri::Neoguri(PartsMgr *mgr) : InGamePart(mgr, 710, FirstFloor - 24)
{
	// �ʱ������� ���� ��ǥ
	floorList.push_back(FirstFloor - 20);
	floorList.push_back(SecondFloor - 20);
	floorList.push_back(ThirdFloor - 20);
	floorList.push_back(FourthFloor - 20);
	floorList.push_back(FifthFloor - 20);
	numOfFloorOn = floorList[0];
	// boundary ����
	boundary[0] = { 50,90,670,510 };
	boundary[1] = { 665,440,745,515 };
	// ��ü �ִϸ����� �����
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

	// �ʱ��� ��ü (�»�� : �׸��� ������)
	// �߾����� �׸��� ���� �ٸ� (�ߴ� : pos) // ���̿� ���Ϳ� �ٸ��� collider���� ����
	for (auto &body : _body)
		body.second->UpdateAnimeCoord(pos.x - 21, pos.y - 24);

	// EventBus

}

void Neoguri::Update()
{
	if (!(state == FALL || state == DIE))
	{
		UpdatePosition();
		// �߾����� �׸��� ���� �ٸ� (���ϴ� : pos) (�»�� : �׸��� ������)
		_body[state]->UpdateAnimeCoord(pos.x - 21, pos.y - 24);
	}
	else
	{
		DiePhase();
	}
	// ������ �������� �ʱ��� ��ġ�� partMgr���� �˷��ֱ�
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

		// ���� ������ ������ ������ ���ڸ� ������ �־���Ѵ�
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
					cout << "�׷� ��� ���Գ�?" << endl;
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
	
	// ���� Ÿ�Ը��� switch��
	switch (state)
	{
		// ���� ����
		case Neoguri::JUMP_L :
		{
			// ���� ����
			if (justBefore == S_LEFT)
			{
				jumpheight = 25;
				changeRateX = -5;
				changeRateY = -5;
			}
			// ���� ����
			if (justBefore == M_LEFT)
			{
				jumpheight = 35;
				changeRateX = -7;
				changeRateY = -5;
			}
			
		}	break;
		// ������ ����
		case Neoguri::JUMP_R:
		{
			// ���� ����
			if (justBefore == S_RIGHT)
			{
				jumpheight = 25;
				changeRateX = +5;
				changeRateY = -5;
			}
			// ���� ����
			if (justBefore == M_RIGHT)
			{
				jumpheight = 35;
				changeRateX = +7;
				changeRateY = -5;
			}

		}	break;
		// ���ڸ� ����
		case Neoguri::JUMP_I:
		{
			// ���� ����
			if (justBefore == IDLE)
			{
				jumpheight = 25;
				changeRateX = 0;
				changeRateY = -5;
			}
			
		}	break;
	}
	// ������ �ٴٸ��� �ö󰡴°� false �������°� true
	if (pos.y <= InGamePart::numOfFloorOn - jumpheight)
	{
		isGoingUp = false;
		isGoingDown = true;
	}
	// �ʱ��� ��ġ�� �ٲٴ� �˰���
	pos.x += changeRateX;
	if (isGoingUp) {
		pos.y += changeRateY;
	}
	else if(isGoingDown)
	{
		//�������� �ִ� ���� �Ǵ�
		pos.y -= changeRateY;
		// ���� �����ߴ��� �Ǵ�
		if (pos.y >= numOfFloorOn)
		{
			justBefore = state;
			pos.y = numOfFloorOn;
			isGoingDown = false;
			_body[state]->ResetAnimeImageOrder();
			// ���� �Է��� ó�� ��������
			if (justBefore == JUMP_I)		state = IDLE;
			else if (justBefore == JUMP_L)  state = S_LEFT;
			else if (justBefore == JUMP_R)  state = S_RIGHT;
			Notify(LAND);
		}
	}
	else
		cout << "���������� �ȵǴµ�...�̹� �ٶ������µ�" << endl;

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

	// ���� ���� �����ߵ�
	if (state == CLIMB)
	{
		// ���� �ö󰥶�
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
	// ���������� ��� �θ� ������ 
	// �ѹ��� ������.
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
