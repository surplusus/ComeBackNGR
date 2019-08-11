#include "stdafx.h"
#include "FmodSound.h"

CFmodSound::CFmodSound(void)
{
	// FMOD system 포인터 변수 초기화
	FMOD_System_Create(&m_pSystem);
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);
}


CFmodSound::~CFmodSound(void)
{
	FMOD_System_Close(m_pSystem);
	FMOD_System_Release(m_pSystem);
}

void CFmodSound::CreateBGSound(int nCount, vector<string> SoundFileName)
// nCount : 사운드 갯수 // SoundFileName : 사운드 이름 vector
{
	// 백 그라운드 사운드 생성

	m_nBGSoundCount = nCount;
	// (m_ppBGSound는 이중포인터이므로 nCount 만큼 new 하는 듯)
	m_ppBGSound = new FMOD_SOUND*[nCount];
	// 중단을 위해서 channel을 만들어 맴버로 저장해 놓는다
	m_ppBGChannel = new FMOD_CHANNEL*[nCount];
	// 사운드 초기화 및 로딩
	for (int i = 0; i < nCount; i++) {
		FMOD_System_CreateSound(m_pSystem, SoundFileName[i].data(), FMOD_LOOP_NORMAL, 0, &m_ppBGSound[i]);
	}
}

void CFmodSound::CreateEffectSound(int nCount, vector<string> SoundFileName)
// nCount : 사운드 갯수 // SoundFileName : 사운드 이름 vector
{
	// 효과 사운드 생성
	m_nEFSoundCount = nCount;
	m_ppEFFSound = new FMOD_SOUND*[nCount];
	
	// 사운드 초기화 및 로딩
	for (int i = 0; i < nCount; i++)
		FMOD_System_CreateSound(m_pSystem, SoundFileName[i].data(), FMOD_DEFAULT, 0, &m_ppEFFSound[i]);
}

void CFmodSound::PlaySoundEffect(int nIndex)
{
	if (nIndex < m_nEFSoundCount)
	{
		// 1회용으로 사용할 빈 channel을 만든다
		FMOD_CHANNEL *pChannel = NULL;
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_ppEFFSound[nIndex], 0, &pChannel);
	}
}

void CFmodSound::PlaySoundBG(int nIndex)
{
	if (nIndex < m_nBGSoundCount)
	{
		// 효과음과 달리 클래스 맴버로 유지되는 channel을 사용한다
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_ppBGSound[nIndex], 0, &m_ppBGChannel[nIndex]);
	}
}

void CFmodSound::StopSoundBG(int nIndex)
{
	if (nIndex < m_nBGSoundCount)
	{
		FMOD_Channel_Stop(m_ppBGChannel[nIndex]);
	}
}

void CFmodSound::ReleaseSound()
{
	int i;
	// FMOD 해제
	delete[] m_ppBGChannel;
	// 배경음 해제(이중포인터 사용)
	for (i = 0; i < m_nBGSoundCount; i++)
		FMOD_Sound_Release(m_ppBGSound[i]);
	delete[] m_ppBGSound;
	// 효과음 해제(이중포인터 사용)
	for (i = 0; i < m_nEFSoundCount; i++)
		FMOD_Sound_Release(m_ppEFFSound[i]);
	delete[] m_ppEFFSound;
}

void CFmodSound::Update()
{
	if (!m_pSystem)
		FMOD_System_Update(m_pSystem);
}

const int CFmodSound::GetBGSoundCound() const
{
	return m_nBGSoundCount;
}
