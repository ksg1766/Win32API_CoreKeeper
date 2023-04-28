#pragma once
#include "Define.h"

class CKeyManager
{
public:
	CKeyManager();
	~CKeyManager();

public:
	bool			Key_Pressing(int _iKey);
	bool			Key_Down(int _iKey);
	bool			Key_Up(int _iKey);

public:

private:
	bool				m_bKeyState[VK_MAX];
};

