#include "stdafx.h"
#include "ScrollManager.h"


CScrollManager::CScrollManager() :m_fScrollX(0.f), m_fScrollY(0.f), m_dwTime(0)
{
}


CScrollManager::~CScrollManager()
{
	Release();
}

void CScrollManager::ScrollShaking()
{
	if (m_dwTime)
	{
		if (m_dwTime % 2)
		{
			Set_ScrollX(-10.f);
			Set_ScrollY(-10.f);
		}
		else
		{
			Set_ScrollX(+10.f);
			Set_ScrollY(+10.f);
		}
		--m_dwTime;
	}
}

void CScrollManager::StartScrollShaking(int _iCount)
{
	m_dwTime = _iCount;
}

void CScrollManager::Initialize()
{
}

void CScrollManager::Release()
{
}
