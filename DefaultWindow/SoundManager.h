#pragma once
#include "Enum.h"

class CSoundManager
{
public:
	CSoundManager();
	virtual ~CSoundManager();

	void Initialize();
	void Release();

public:
	void PlaySound(TCHAR* pSoundKey, CHANNELID eID, float fVolume = 1.f);
	void PlayBGM(TCHAR* pSoundKey, float fVolume = 1.f);
	void StopSound(CHANNELID eID);
	void StopAll();
	void SetChannelVolume(CHANNELID eID, float fVolume);

	float	GetVolume() { return m_fVolume; }
	void	SetVolume(float _fVolume)
	{
		m_fVolume += _fVolume;
		if (m_fVolume > 1.f)
			m_fVolume = 1.f;
		if (m_fVolume < 0.f)
			m_fVolume = 0.f;
	}


private:
	void LoadSoundFile();

private:
	// ���� ���ҽ� ������ ���� ��ü 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;

	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannelArr[(UINT)CHANNELID::MAXCHANNEL];

	// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pSystem;

	float	m_fVolume;
};

