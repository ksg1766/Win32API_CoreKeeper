#include "stdafx.h"
#include "PickAxe.h"
#include "Collider.h"
#include "Graphics.h"
#include "Managers.h"
#include "Player.h"

CPickAxe::CPickAxe()
{
}


CPickAxe::~CPickAxe()
{
}

void CPickAxe::Initialize()
{
	m_eType = TYPE::ITEM;
	m_eItemType = ITEM::WEAPON;

	m_vPosition = m_pOwner->GetPosition();
	m_vScale = Vector2(120.f, 120.f);

	m_ePreState = STATE::END;
	m_eCurState = STATE::IDLE;

	m_pCollider = new CCollider;
	m_pGraphics = new CGraphics;
	m_pCollider->Initialize(this);
	m_pGraphics->Initialize(this);
	m_pFrameKey = L"PickAxeWood";
	m_eDir = m_pOwner->GetDir();
}

int CPickAxe::Update(void)
{
	m_eDir = m_pOwner->GetDir();
	m_vPosition = m_pOwner->GetPosition();
	m_ePreState = m_eCurState;
	m_eCurState = m_pOwner->GetState();
	return 0;
}

int CPickAxe::LateUpdate(void)
{
	if (STATE::ATTACK != m_eCurState)
		m_pCollider->SetScale(Vector2::Zero());
	else
		m_pCollider->SetScale(m_pOwner->GetScale());
	
	m_pCollider->LateUpdate();

	MoveFrame();
	SetMotion();

	return 0;
}

void CPickAxe::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	m_pGraphics->Render(hDC, hMemDC);
	m_pCollider->Render(hDC);
	//if (STATE::ATTACK == m_eCurState)
	//	m_parrEquipment[(UINT)ITEM::WEAPON]->Render(hDC);
}

void CPickAxe::Release(void)
{
}

void CPickAxe::SetMotion(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case STATE::IDLE:
		case STATE::MOVE:
			if (m_eDir == DIR::RIGHT)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 30;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::UP)
			{
				m_tFrame.iFrameStart = 3;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 30;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::LEFT)
			{
				m_tFrame.iFrameStart = 6;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 6;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 30;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::DOWN)
			{
				m_tFrame.iFrameStart = 9;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 9;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 30;
				m_tFrame.dwTime = GetTickCount();
			}
			break;
		case STATE::ATTACK:
			if (m_eDir == DIR::RIGHT)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 2;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::UP)
			{
				m_tFrame.iFrameStart = 3;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 5;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::LEFT)
			{
				m_tFrame.iFrameStart = 6;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 8;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::DOWN)
			{
				m_tFrame.iFrameStart = 9;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 11;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 50;
				m_tFrame.dwTime = GetTickCount();
			}
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CPickAxe::MoveFrame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;

		m_tFrame.dwTime = GetTickCount();
	}
}