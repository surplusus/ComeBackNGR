#pragma once
#include "FMOD Studio API Windows/api/core/inc/fmod.h"
#pragma comment(lib,"fmod_vc.lib")
class EventSoundPlay;

class SoundMgr
{
private:
	static SoundMgr* instance;
	SoundMgr() {}
	~SoundMgr() {}
public:
	static SoundMgr* GetInstance();
	static void Release();
public:
	enum SOUNDTYPE{
		die=0,
		fall=1,
		monster,
		jump,
		open,
		run,
		SD_END
	};
public:
	FMOD_SYSTEM* g_SoundSystem;
	FMOD_SOUND* g_Sound[6];
	FMOD_CHANNELGROUP* g_Soundchannelgroup[6];
	FMOD_CHANNEL* g_channel[6];
	float volume = 0.8f;
	FMOD_BOOL isPlaying = false;

	void Init();
	void ReleaseSound();
	//void PlaySound(SOUNDTYPE idSound);
	void PlayMySound(int idSound);
	void PlayCursorMoveMySound(EventSoundPlay*);
};

