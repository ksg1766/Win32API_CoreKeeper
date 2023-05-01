#include "stdafx.h"
#include "Glurch.h"
#include "Collider.h"
#include "Graphics.h"
#include "Managers.h"

CGlurch::CGlurch()
{
}


CGlurch::~CGlurch()
{
}

void CGlurch::Initialize(void)
{
	m_IsDead = false;
	m_eType = TYPE::BOSS;
	m_vPosition = Vector2(900.f, 800.f);
	m_vScale = Vector2(256.f, 256.f);
	m_iRange = 13 * TILECX;

	m_ePreState = STATE::END;
	m_eCurState = STATE::IDLE;

	m_pCollider = new CCollider;
	m_pGraphics = new CGraphics;

	m_pCollider->Initialize(this);
	m_pGraphics->Initialize(this);

	m_fSpeed = 10.f;

	m_fTime = 0;

	m_pFrameKey = L"Glurch";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
}

int CGlurch::Update(void)
{
	Action();
	return 0;
}

int CGlurch::LateUpdate(void)
{
	m_pCollider->LateUpdate();

	MoveFrame();
	SetMotion();

	return 0;
}

void CGlurch::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	m_pGraphics->Render(hDC, hMemDC);
	m_pCollider->Render(hDC);
}



void CGlurch::Release(void)
{
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pGraphics);
}

void CGlurch::Action()
{
}

void CGlurch::SetMotion(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case STATE::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::MOVE:		// Jump in this case
			m_tFrame.iFrameStart = 8;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameEnd;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::ATTACK:		// Take down in this case
			m_tFrame.iFrameStart = 16;
			m_tFrame.iFrameEnd = 18;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CGlurch::MoveFrame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (STATE::IDLE == m_eCurState)
		{
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
		}
		else if (STATE::MOVE == m_eCurState)
		{
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
		}
		else
		{
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
		}

		m_tFrame.dwTime = GetTickCount();
	}
}

void CGlurch::OnCollisionEnter(CCollider * _pOther)
{
}

void CGlurch::OnCollisionStay(CCollider * _pOther)
{
}

void CGlurch::OnCollisionExit(CCollider * _pOther)
{
}