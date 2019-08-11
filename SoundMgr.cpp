#include "stdafx.h"
#include "SoundMgr.h"
#include "FmodSound.h"

SoundMgr* SoundMgr::instance = nullptr;

SoundMgr::~SoundMgr()
{
	soundSystem->ReleaseSound();
}

SoundMgr * SoundMgr::GetInstance()
{
	if (!instance)
	{
		instance = new SoundMgr;
	}
	return instance;
}

void SoundMgr::Release()
{
	delete instance;
}

void SoundMgr::InitSound()
{
	soundSystem = new CFmodSound;
	soundSystem->CreateBGSound(1, fileNameBG);
	soundSystem->CreateEffectSound(4, fileNameEffect);
#ifdef _DEBUG
	cout << "사운드 시스템 준비완료" << endl;
#endif // _DEBUG
}

void SoundMgr::Init()
{
	InitSound();
}

void SoundMgr::PlayBGSound(SOUNDTYPE soundtype)
{
	switch (soundtype)
	{
	case SoundMgr::BGOPEN:
		soundSystem->PlaySoundBG(0);
		break;
	case SoundMgr::BGMON:
		soundSystem->PlaySoundBG(1);
		break;
	}
	soundSystem->Update();
}

void SoundMgr::PlayEffectSound(SOUNDTYPE soundtype)
{
	switch (soundtype)
	{
	case SoundMgr::RUN:
		soundSystem->PlaySoundEffect(0);
		break;
	case SoundMgr::JUMP:
		soundSystem->PlaySoundEffect(1);
		break;
	case SoundMgr::FALL:
		soundSystem->PlaySoundEffect(2);
		break;
	case SoundMgr::DIE:
		soundSystem->PlaySoundEffect(3);
		break;
	}
	soundSystem->Update();
}

void SoundMgr::StopBGSound()
{
	int cntBG = soundSystem->GetBGSoundCound();
	for (size_t i = 0; i < cntBG; i++)
	{
		soundSystem->StopSoundBG(i);
	}
}
