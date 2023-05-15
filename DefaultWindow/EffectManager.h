#pragma once
#include "Vector2.h"

class CEffectManager
{
public:
	CEffectManager();
	virtual ~CEffectManager();

	void	Render();

	bool	IsOnPlay() { return m_OnPlay; }
	Vector2	GetEffectPos() { return m_vEffectPos; }
	DWORD	GetTime() { return m_dwTime; }
	DWORD	GetTime2() { return m_dwTime2; }

	void	SetEffectOn(Vector2 _vEffectPos) { m_vEffectPos = _vEffectPos; m_OnPlay = true; }
	void	SetOnPlay(bool _OnPlay) {	m_OnPlay = _OnPlay; }
	void	SetTime1(DWORD _dwTime = GetTickCount()) { m_dwTime = _dwTime; };
	void	SetTime2(DWORD _dwTime2 = GetTickCount()) { m_dwTime2 = _dwTime2; };
	void	SetTimer(DWORD _dwTime = GetTickCount(), DWORD _dwTime2 = GetTickCount()) { if(m_OnPlay) m_dwTime = _dwTime; m_dwTime2 = _dwTime2; }
	void	DeadEffect();

private:
	bool		m_OnPlay;

	Vector2		m_vEffectPos;

	DWORD		m_dwTime;
	DWORD		m_dwTime2;
};

