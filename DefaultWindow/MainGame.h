#pragma once

#include "Define.h"
#include "Player.h"

class CMainGame
{
public:
	void		Initialize(void);
	void		Update(void);
	void		LateUpdate(void);
	void		Render(void);
	void		Release(void);

public:

private:

	HDC			m_DC;
	int			m_iFPS;
	TCHAR		m_szFPS[32];
	DWORD		m_dwTime;

public:
	CMainGame();
	~CMainGame();
};

