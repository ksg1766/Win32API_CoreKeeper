#include "stdafx.h"
#include "GlowEffect.h"
#include "Graphics.h"
#include "Managers.h"

CGlowEffect::CGlowEffect()
{
}

CGlowEffect::~CGlowEffect()
{
	Release();
}

void CGlowEffect::Initialize(void)
{
	m_eType = TYPE::EFFECT;
	m_eRender = RENDERID::EFFECT;
	m_eEffectType = EFFECT_TYPE::GLOW;

	m_IsDead = true;	// Pool에 dead 상태로 보관
	m_eDir = DIR::END;
	m_vPosition = Vector2::Zero();
	m_vScale = Vector2(24.f, 24.f);

	m_pFrameKey = L"GlowEffect";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.dwTime = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.iMotion = 0;

	m_dwTime = 0;

	m_fSpeed = 0.f;

	m_pCollider = nullptr;
	m_pRigidBody = nullptr;
	m_pGraphics = new CGraphics;
	m_pGraphics->Initialize(this);
}

int CGlowEffect::Update(void)
{
	return 0;
}

int CGlowEffect::LateUpdate(void)
{
	SetMotion();
	MoveFrame();
	return 0;
}

void CGlowEffect::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	m_pGraphics->Render(hDC, hMemDC);
}

void CGlowEffect::Release(void)
{
	Safe_Delete(m_pGraphics);
}

void CGlowEffect::SetMotion(void)
{
}

void CGlowEffect::MoveFrame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
			CManagers::instance().Event()->DeleteObject(this);
		}
		m_tFrame.dwTime = GetTickCount();
	}
}
