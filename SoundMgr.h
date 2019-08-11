#pragma once
class CFmodSound;

class SoundMgr
{
private:
	static SoundMgr* instance;
	SoundMgr() {}
	~SoundMgr();
public:
	static SoundMgr* GetInstance();
	static void Release();
private:
	std::vector<std::string> fileNameEffect
		= { "run.wav", "jump.wav","fall.wav", "die.wav" };
	std::vector<std::string> fileNameBG
		= {"open.wav","monster.wav"};
	CFmodSound* soundSystem;

	void InitSound();
public:
	enum SOUNDTYPE{	BGOPEN = 0, BGMON = 1,
			RUN = 0, JUMP = 1,FALL =2, DIE =3,
	};
	void Init();
	void PlayBGSound(SOUNDTYPE);
	void PlayEffectSound(SOUNDTYPE);
	void StopBGSound();
};

