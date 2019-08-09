#pragma once

class SoundMgr
{
private:
	static SoundMgr* instance;
	SoundMgr() {}
	~SoundMgr() {}
public:
	static SoundMgr* GetInstance();
	static void Release();
private:
	enum {
		die=0,
		fall=1,
		monster,
		jump,
		open,
		run,
	};
public:
	FMOD_SYSTEM g_SoundSystem;
	FMOD_SOUND g_Sound[6];
	FMOD_CHANNEL g_channel = NULL;
	float volume = 0.8f;
	FMOD_BOOL isPlaying = false;

	void Init();
	void ReleaseSound();
};

