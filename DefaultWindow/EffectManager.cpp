#include "stdafx.h"
#include "EffectManager.h"
#include "Enum.h"
#include "Managers.h"

CEffectManager::CEffectManager(): m_OnPlay(false)
{
}

void CEffectManager::Render()
{
}

void CEffectManager::DeadEffect()
{
    if (m_dwTime2 + 30000 > GetTickCount())
	{
		if (m_dwTime + 150 <= GetTickCount())
		{
			CManagers::instance().Pool()->PlayEffect(EFFECT_TYPE::HIT, m_vEffectPos + 10.f * Vector2::MyRandVec2());
      		m_dwTime = GetTickCount();
		}
	}
	else
		m_OnPlay = false;
}


CEffectManager::~CEffectManager()
{
}
