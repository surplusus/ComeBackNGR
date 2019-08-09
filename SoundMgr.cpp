#include "stdafx.h"
#include "SoundMgr.h"
#include <conio.h>
#include<windows.h>
#include <playsoundapi.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define _CRT_SECURE_NO_WARNINNGS

SoundMgr* SoundMgr::instance = nullptr;

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

void SoundMgr::Init()
{
	//char str[128];
	wchar_t str2[128];
	/*FMOD_System_Create(&g_SoundSystem);
	FMOD_System_Init(g_SoundSystem, 6, FMOD_INIT_NORMAL, NULL);
	FMOD_System_CreateSound(g_SoundSystem, "Sound/die.wav", FMOD_DEFAULT, 0, &g_Sound[die]);
	FMOD_System_CreateSound(g_SoundSystem, "Sound/fall.wav", FMOD_DEFAULT, 0, &g_Sound[fall]);
	FMOD_System_CreateSound(g_SoundSystem, "Sound/monster.wav", FMOD_DEFAULT, 0, &g_Sound[monster]);
	FMOD_System_CreateSound(g_SoundSystem, "Sound/neogurijump.wav", FMOD_DEFAULT, 0, &g_Sound[jump]);
	FMOD_System_CreateSound(g_SoundSystem, "Sound/neoguriopen.wav", FMOD_DEFAULT, 0, &g_Sound[open]);
	FMOD_System_CreateSound(g_SoundSystem, "Sound/neogurirun.wav", FMOD_DEFAULT, 0, &g_Sound[run]);*/
	for (int i = 0; i < SD_END; i++)
	{
		wsprintf(str2, L"open ./Sound/sound%d.wav alias %d", i + 1, i);
		mciSendString(str2, NULL, 0, 0);
	}
	EventBus::GetInstance()->Subscribe(this, &SoundMgr::PlayCursorMoveMySound);
}

void SoundMgr::ReleaseSound()
{
	//for (auto &s : g_Sound)
	//	FMOD_Sound_Release(s);
	//FMOD_System_Close(g_SoundSystem);
	//FMOD_System_Release(g_SoundSystem);
}

void SoundMgr::PlayMySound(int idSound)
{
	wchar_t str[128];
	wsprintf(str, L"play %d", idSound);
	mciSendString(str, NULL, 0, 0);
}

void SoundMgr::PlayCursorMoveMySound(EventSoundPlay* evnt)
{
	//play Cursor1 뒤에 from 0을 이용해서 음악파일을 처음부터 재생하도록함
	int idSound = evnt->GetSoundID();
	wchar_t str[128];
	wsprintf(str, L"play %d from 0", idSound);
	mciSendString(str, NULL, 0, 0);
}

