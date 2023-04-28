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

public:
	CMainGame();
	~CMainGame();
};

