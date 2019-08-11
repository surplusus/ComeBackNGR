#include "stdafx.h"
#include "FmodSound.h"

CFmodSound::CFmodSound(void)
{
	// FMOD system ������ ���� �ʱ�ȭ
	FMOD_System_Create(&m_pSystem);
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);
}


CFmodSound::~CFmodSound(void)
{
	FMOD_System_Close(m_pSystem);
	FMOD_System_Release(m_pSystem);
}

void CFmodSound::CreateBGSound(int nCount, vector<string> SoundFileName)
// nCount : ���� ���� // SoundFileName : ���� �̸� vector
{
	// �� �׶��� ���� ����

	m_nBGSoundCount = nCount;
	// (m_ppBGSound�� �����������̹Ƿ� nCount ��ŭ new �ϴ� ��)
	m_ppBGSound = new FMOD_SOUND*[nCount];
	// �ߴ��� ���ؼ� channel�� ����� �ɹ��� ������ ���´�
	m_ppBGChannel = new FMOD_CHANNEL*[nCount];
	// ���� �ʱ�ȭ �� �ε�
	for (int i = 0; i < nCount; i++) {
		FMOD_System_CreateSound(m_pSystem, SoundFileName[i].data(), FMOD_LOOP_NORMAL, 0, &m_ppBGSound[i]);
	}
}

void CFmodSound::CreateEffectSound(int nCount, vector<string> SoundFileName)
// nCount : ���� ���� // SoundFileName : ���� �̸� vector
{
	// ȿ�� ���� ����
	m_nEFSoundCount = nCount;
	m_ppEFFSound = new FMOD_SOUND*[nCount];
	
	// ���� �ʱ�ȭ �� �ε�
	for (int i = 0; i < nCount; i++)
		FMOD_System_CreateSound(m_pSystem, SoundFileName[i].data(), FMOD_DEFAULT, 0, &m_ppEFFSound[i]);
}

void CFmodSound::PlaySoundEffect(int nIndex)
{
	if (nIndex < m_nEFSoundCount)
	{
		// 1ȸ������ ����� �� channel�� �����
		FMOD_CHANNEL *pChannel = NULL;
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_ppEFFSound[nIndex], 0, &pChannel);
	}
}

void CFmodSound::PlaySoundBG(int nIndex)
{
	if (nIndex < m_nBGSoundCount)
	{
		// ȿ������ �޸� Ŭ���� �ɹ��� �����Ǵ� channel�� ����Ѵ�
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
	// FMOD ����
	delete[] m_ppBGChannel;
	// ����� ����(���������� ���)
	for (i = 0; i < m_nBGSoundCount; i++)
		FMOD_Sound_Release(m_ppBGSound[i]);
	delete[] m_ppBGSound;
	// ȿ���� ����(���������� ���)
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
