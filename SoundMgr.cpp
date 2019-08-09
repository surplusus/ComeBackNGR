#include "stdafx.h"
#include "SoundMgr.h"
#include <fmod.h>
#include <conio.h>
#pragma comment(lib,"./FMOD Studio API Windows/api/core/lib/x86/fmod_vc.lib")

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
	FMOD_System_Create(&g_SoundSystem);
	FMOD_System_Init(g_SoundSystem, 32, FMOD_INIT_NORMAL, NULL);
	FMOD_System_CreateSound(g_SoundSystem, "Sound/die.wav", FMOD_DEFAULT, 0, &g_Sound[die]);
	FMOD_System_CreateSound(g_SoundSystem, "Sound/fall.wav", FMOD_DEFAULT, 0, &g_Sound[fall]);
	FMOD_System_CreateSound(g_SoundSystem, "Sound/monster.wav", FMOD_DEFAULT, 0, &g_Sound[monster]);
	FMOD_System_CreateSound(g_SoundSystem, "Sound/neogurijump.wav", FMOD_DEFAULT, 0, &g_Sound[jump]);
	FMOD_System_CreateSound(g_SoundSystem, "Sound/neoguriopen.wav", FMOD_DEFAULT, 0, &g_Sound[open]);
	FMOD_System_CreateSound(g_SoundSystem, "Sound/neogurirun.wav", FMOD_DEFAULT, 0, &g_Sound[run]);
}

void SoundMgr::ReleaseSound()
{
	FMOD_Sound_Release(g_Sound);
	FMOD_System_Close(g_SoundSystem);
	FMOD_System_Release(g_SoundSystem);
}
