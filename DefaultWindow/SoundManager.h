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
	// 사운드 리소스 정보를 갖는 객체 
	map<TCHAR*, FMOD_SOUND*> m_mapSound;

	// FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannelArr[(UINT)CHANNELID::MAXCHANNEL];

	// 사운드 ,채널 객체 및 장치를 관리하는 객체 
	FMOD_SYSTEM* m_pSystem;

	float	m_fVolume;
};

