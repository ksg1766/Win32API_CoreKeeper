#include "stdafx.h"
#include "HitEffect.h"
#include "Graphics.h"
#include "Managers.h"

CHitEffect::CHitEffect()
{
}

CHitEffect::~CHitEffect()
{
	Release();
}

void CHitEffect::Initialize(void)
{
	m_eType = TYPE::EFFECT;
	m_eRender = RENDERID::EFFECT;
	m_eEffectType = EFFECT_TYPE::HIT;

	m_IsDead = true;	// Pool�� dead ���·� ����
	m_eDir = DIR::END;
	m_vPosition = Vector2::Zero();
	m_vScale = Vector2(96.f, 96.f);

	m_pFrameKey = L"HitEffect";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	m_tFrame.iFrameEnd = 4;
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

int CHitEffect::Update(void)
{
	return 0;
}

int CHitEffect::LateUpdate(void)
{
	SetMotion();
	MoveFrame();

	return 0;
}

void CHitEffect::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	m_pGraphics->Render(hDC, hMemDC);
}

void CHitEffect::Release(void)
{
	Safe_Delete(m_pGraphics);
}

void CHitEffect::SetMotion(void)
{
	//
	//m_tFrame.dwTime = GetTickCount();
}

void CHitEffect::MoveFrame(void)
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
