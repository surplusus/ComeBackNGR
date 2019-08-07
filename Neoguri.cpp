#include "stdafx.h"
#include "Neoguri.h"
#include "Basic_Value.h"
#include "Animator.h"
using std::cout;
using std::endl;
Neoguri::Neoguri(PartsMgr *mgr) : InGamePart(mgr, 700, FirstFloor)
{
	// ��ü �ִϸ����� �����
	_body[IDLE] = new Animator(IDB_BITMAP_IDLE1, 6);
	_body[M_LEFT] = new Animator(IDB_BITMAP_MLEFT1, 5);
	_body[M_RIGHT] = new Animator(IDB_BITMAP_MRIGHT1, 5);
	_body[FALL] = new Animator(IDB_BITMAP_FALL1, 4);
	_body[JUMP_R] = new Animator(IDB_BITMAP_RIGHTJUMP1, 8);
	_body[JUMP_L] = new Animator(IDB_BITMAP_LEFTJUMP1, 8);
	_body[CLIMB] = new Animator(IDB_BITMAP_CLIMB1, 2);
	_body[S_LEFT] = _body[M_LEFT];
	_body[S_RIGHT] = _body[M_RIGHT];
	_body[DIE] = _body[FALL];
	_body[JUMP_I] = _body[IDLE];

	// �ʱ��� ó�� ��ġ body�� update
	for (auto &body : _body)
		body.second->UpdateAnimeCoord(pos.x, pos.y);

	TimeMgr* time = TimeMgr::GetInstance();
	time->SetPeriod("NEOGURI");
}

void Neoguri::Update()
{
	if (!(state == FALL || state == DIE))
	{

		UpdatePosition();
		UpdateBodyAnime();
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
		_body[M_LEFT]->	DrawAnime(true,100);
		break;
	case Neoguri::M_RIGHT:
		_body[M_RIGHT]->DrawAnime(true, 100);
		break;
	case Neoguri::S_LEFT:
		_body[S_LEFT]->	DrawAnime(false, 100);
		break;
	case Neoguri::S_RIGHT:
		_body[S_RIGHT]->DrawAnime(false, 100);
		break;
	case Neoguri::JUMP_I:
		_body[IDLE]->	DrawAnime(true, 40);
		break;
	case Neoguri::JUMP_R:
		_body[JUMP_R]->	DrawAnime(true, 40);
		break;
	case Neoguri::JUMP_L:
		_body[JUMP_L]->	DrawAnime(true, 40);
		break;
	case Neoguri::CLIMB:
		_body[CLIMB]->	DrawAnime(true, 100);
		break;
	case Neoguri::IDLE:
		_body[IDLE]->DrawAnime(false, 100);
		break;
	case Neoguri::FALL:
		_body[FALL]->DrawAnime(true, 100);
		break;
	case Neoguri::DIE:
		_body[DIE]->DrawAnime(false, 100);
		break;
	default:
		break;
	}

}

void Neoguri::KeepPosInside()
{
	if (pos.x < MapMinWidth)	pos.x = MapMinWidth;
	if (pos.y < MapMinHeight)	pos.y = MapMinHeight;
	if (pos.x > MapMaxWidth) 	pos.x = MapMaxWidth;
	if (pos.y > MapMaxHeight)	pos.y = MapMaxHeight;
}

void Neoguri::UpdatePosition()
{
	if (state == FALL || state == DIE)
		return;

	int speed = 10;
	int keyFlag = key->CheckKey();
	
	if (time->Alarm("NEOGURIMOVE",40,0))
	{
		static STATE justBefore = IDLE;

		// ���� ������ ������ ������ ���ڸ� ������ �־���Ѵ�
		if (isGoingUp == false && isGoingDown == false)
		{
			if ((keyFlag & key->K_SPACE))
			{
				isGoingUp = true;
				state = JUMP;
			}
		}
		// �ö󰡰ų� �������� ���̶�� Jump�� ����
		if (isGoingUp)
			Jump(justBefore, isGoingUp, isGoingDown);
		else if (isGoingDown)
			Jump(justBefore, isGoingUp, isGoingDown);
		else
		{
			if (isOnLadder)
				justBefore = MoveUD(justBefore);
			else
				justBefore = MoveLR(justBefore);
		}
		
	}
	
	KeepPosInside();
}

void Neoguri::UpdateBodyAnime()
{
	_body[state]->UpdateAnimeCoord(pos.x, pos.y);
}

Neoguri::STATE Neoguri::Jump(STATE justBefore, bool& goUp, bool& goDown)
{
	int jumpheight;
	int changeRateX;
	int changeRateY;
	STATE returnstate = justBefore;
	// ���� �Է��� ó�� ��������
	if (state == JUMP)
	{
		if (justBefore == M_LEFT || justBefore == S_LEFT)
			state = JUMP_L;
		if (justBefore == M_RIGHT || justBefore == S_RIGHT)
			state = JUMP_R;
		if (justBefore == IDLE)
			state = JUMP_I;
	}
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
	if (isGoingUp)
		pos.y += changeRateY;
	else if(isGoingDown)
	{
		pos.y -= changeRateY;
		// ���� �����ߴ��� �Ǵ�
		if (pos.y >= numOfFloorOn)
		{
			pos.y = numOfFloorOn;
			isGoingDown = false;
		}
	}
	else
		cout << "���������� �ȵǴµ�...�̹� �ٶ������µ�" << endl;

	return justBefore;
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

Neoguri::STATE Neoguri::MoveUD(STATE)
{
	int keyFlag = key->CheckKey();
	int speed = 10;

	if (keyFlag & key->K_DOWN) {
		pos.y += speed;
		state = CLIMB;
	}
	else if (keyFlag & key->K_UP) {
		pos.y -= speed;
		state = CLIMB;
	}

	// ���� ���� �����ߵ�
	if (pos.y == 700)
	{
		state = IDLE;
		isOnLadder = false;
	}
	return IDLE;
}

Neoguri::STATE Neoguri::DiePhase()
{
	if (pos.y < FirstFloor)
	{
		pos.y -= 10;
		_body[FALL]->UpdateAnimeCoord(pos.x, pos.y);
		return STATE::FALL;
	}
	else
	{
		state = DIE;
		Notify(DIE);
		return STATE::DIE;
	}
}

bool Neoguri::ToggleLadderState()
{
	// ���������� ��� �θ� ������ 
	// �ѹ��� ������.
	if (state != CLIMB)
	{
		state = CLIMB;
		return isOnLadder = !isOnLadder;
	}
	// �ö󰡴� ���¿��� �ʱ����� isOnLadder�� �� �� �ִ�.
	if (state == CLIMB && isOnLadder == false)
	{
		state = IDLE;
		return isOnLadder;
	}
	return false;
}

void Neoguri::Die()
{
	state = FALL;
}
