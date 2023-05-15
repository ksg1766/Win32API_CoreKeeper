#include "stdafx.h"
#include "Cocoon.h"
#include "Collider.h"
#include "Graphics.h"
#include "Managers.h"

CCocoon::CCocoon()
{
}


CCocoon::~CCocoon()
{
}

void CCocoon::Initialize(void)
{
	m_eType = TYPE::BOSS;
	m_IsDead = false;
	m_eDir = DIR::END;
	m_eRender = RENDERID::GAMEOBJECT;

	m_iBiom = 2;

	m_iMaxHp = 80;
	m_iHp = m_iMaxHp;

	//m_vPosition = Vector2();
	m_vScale = Vector2(150.f, 150.f);

	m_ePreState = STATE::END;
	m_eCurState = STATE::ATTACK;

	m_pCollider = new CCollider;
	m_pGraphics = new CGraphics;

	m_pCollider->Initialize(this);
	m_pGraphics->Initialize(this);

	m_pFrameKey = L"Cocoon";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 3000;
	m_tFrame.dwTime = 0;
	m_tFrame.dwTime = GetTickCount();
}

int CCocoon::Update(void)
{
	if (m_iHp <= 0)
	{
		m_iHp = 0;
		m_fSpeed = 0;
		m_eCurState = STATE::DEAD;
	}

	if (STATE::DEAD == m_eCurState)
	{
		CManagers::instance().Event()->DeleteObject(this);
		return 0;
	}
	SetMotion();
	MoveFrame();

	return 0;
}

int CCocoon::LateUpdate(void)
{
	m_pCollider->LateUpdate();

	return 0;
}

void CCocoon::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	m_pGraphics->Render(hDC, hMemDC);
}

void CCocoon::Release(void)
{
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pGraphics);
}

void CCocoon::Action()
{
}

void CCocoon::SetMotion(void)
{
	if (m_ePreState != m_eCurState)
	{
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 3;
		m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 3000;
		m_tFrame.dwTime = GetTickCount();

		m_ePreState = m_eCurState;
	}
}

void CCocoon::MoveFrame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;

		// iFrameStart == 3 되면 dead로 전환 // 3은 이미지 없음
		//if (STATE::DEAD == m_eCurState)
		if (3 == m_tFrame.iFrameStart)
		{
			for (int i = 0; i < 4; ++i)
			{
				CManagers::instance().Pool()->CreateMonster(2, m_vPosition + 10 * (i-5) * Vector2::One());
			}

			CManagers::instance().Event()->DeleteObject(this);
		}

		m_tFrame.dwTime = GetTickCount();
	}
}
