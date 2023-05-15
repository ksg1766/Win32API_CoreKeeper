#include "stdafx.h"
#include "Slime.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Graphics.h"
#include "Shadow.h"
#include "Managers.h"
#include "SelectGDI.h"

CSlime::CSlime()
{
}

CSlime::~CSlime()
{
	Release();
}

void CSlime::Initialize(void)
{
	m_IsDead = true;
	m_eType = TYPE::MONSTER;
	m_vPosition = Vector2(600.f, 700.f);

	m_iBiom = 0;

	m_iHp = 20;

	m_iDamage = 5;

	m_vScale = Vector2(64.f, 64.f);
	m_iRange = 7 * TILECX;

	m_vTargetPoint = m_vPosition;
	m_pTarget = nullptr;
	m_ePreState = STATE::END;
	m_eCurState = STATE::IDLE;

	m_pathIndex = 0;

	m_pShadow = new CShadow;
	m_pCollider = new CCollider;
	m_pRigidBody = new CRigidBody;
	m_pGraphics = new CGraphics;

	m_pShadow->SetHost(this);
	m_pShadow->Initialize();
	m_pShadow->SetScale(Vector2(32.f, 8.f));
	m_pShadow->SetFrameKey(L"Slime_Shadow");

	FRAME _tShadowFrame;
	_tShadowFrame.iFrameStart = 0;
	_tShadowFrame.iFrameStartBf = _tShadowFrame.iFrameStart;
	_tShadowFrame.iFrameEnd = 0;
	_tShadowFrame.iMotion = 0;
	_tShadowFrame.dwSpeed = 100;
	_tShadowFrame.dwTime = GetTickCount();
	m_pShadow->SetFrame(_tShadowFrame);

	m_pCollider->Initialize(this);
	m_pRigidBody->Initialize(this);
	m_pGraphics->Initialize(this);

	m_fSpeed = 1.f;

	m_dwTime = 0;

	m_pFrameKey = L"Slime";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 80;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDERID::GAMEOBJECT;
}

int CSlime::Update(void)
{
	if (m_iHp <= 0)
	{
		m_iHp = 0;
		m_fSpeed = 0;
		m_eCurState = STATE::DEAD;
	}

	if (STATE::DEAD == m_eCurState)
		return 0;

	CGameObject* pPlayer = CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::PLAYER).front();
	if (Vector2::Distance(pPlayer->GetPosition(), m_vPosition) <= m_iRange)
	{
		m_pTarget = pPlayer;
	}
	else
	{
		m_pTarget = nullptr;
		m_path.clear();
	}

	if (nullptr != m_pTarget)
	{
		if (STATE::IDLE == m_eCurState)
		{
			//m_vTargetPoint = m_pTarget->GetPosition();
			if (m_dwTime + 300 < GetTickCount())
			{
				m_vTargetPoint = pPlayer->GetPosition();
				AStar();
				m_dwTime = GetTickCount();
			}
			if(Vector2::Distance(pPlayer->GetPosition(), m_vPosition) <= 2 * TILECX)
				m_eCurState = STATE::ATTACK;
		}
	}
	else
	{
		m_vPosition = m_vPosition;
		m_vTargetPoint = m_vPosition;
		m_eCurState = STATE::IDLE;
	}

	Action();

	m_pRigidBody->Update();

	return 0;
}

int CSlime::LateUpdate(void)
{
	if (STATE::DEAD != m_eCurState)
		m_pCollider->LateUpdate();

	MoveFrame();
	SetMotion();

	return 0;
}

void CSlime::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);
	m_pShadow->Render(hDC);
	m_pGraphics->Render(hDC, hMemDC);

	if(	CManagers::instance().Scene()->GetAStarGrid())
	{
		PEN_TYPE ePen = PEN_TYPE::BLUE;

		CSelectGDI temp1(hDC, ePen);
		CSelectGDI temp2(hDC, BRUSH_TYPE::HOLLOW);

		float	fScrollX = CManagers::instance().Scroll()->Get_ScrollX();
		float	fScrollY = CManagers::instance().Scroll()->Get_ScrollY();

		for (auto& iter : m_path)
		{
			int	iX = (TILECX * iter.x) + (TILECX >> 1);
			int	iY = (TILECY * iter.y) + (TILECY >> 1);
			Rectangle(hDC,
				(int)(iX - TILECX / 2.f + fScrollX),
				(int)(iY - TILECY / 2.f + fScrollY),
				(int)(iX + TILECX / 2.f + fScrollX),
				(int)(iY + TILECY / 2.f + fScrollY)
			);
		}
	}
	if (STATE::DEAD != m_eCurState)
		m_pCollider->Render(hDC);
}

void CSlime::Release(void)
{
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pRigidBody);
	Safe_Delete(m_pGraphics);
	Safe_Delete(m_pShadow);
}

void CSlime::Action()
{
	switch (m_eCurState)
	{
	case STATE::IDLE: // 슬라임은 IDLE이 움직임 포함
		if (nullptr != m_pTarget)
		{
			//m_pRigidBody->SetVelocity(m_fSpeed * (m_vTargetPoint - m_vPosition).Normalize());
			//Pos to Vecto2
			int	i = (m_vPosition.x - (TILECX >> 1)) / TILECX;
			int	j = (m_vPosition.y - (TILECY >> 1)) / TILECY;
			if (m_path.size() == 0)
				break;
			if (Pos(i, j) == m_path[m_pathIndex])
			{
				if (m_path.size() > m_pathIndex + 2)
					m_pathIndex += 2;
				else
					++m_pathIndex;
			}
			
			//Vecto2 to Pos
			float	fX = (TILECX * m_path[m_pathIndex].x) + (TILECX >> 1);
			float	fY = (TILECY * m_path[m_pathIndex].y) + (TILECY >> 1);
			
			m_pRigidBody->SetVelocity(m_fSpeed * (Vector2(fX, fY) - m_vPosition).Normalize());
			//m_path[m_pathIndex];
		}
		else
		{
			m_pRigidBody->SetVelocity(Vector2::Zero());
		}
		break;

	case STATE::ATTACK:
		Attack();
		break;
	}
	m_pShadow->SetPosition(Vector2(m_vPosition.x, m_vPosition.y + 10.f));
}

void CSlime::Attack()
{
	m_pShadow->SetPosition(Vector2(m_vPosition.x, m_vPosition.y + 10.f));
	if (16 == m_tFrame.iFrameStart)
	{
		m_pRigidBody->SetVelocity(2 * m_fSpeed * (m_vTargetPoint - m_vPosition).Normalize());
	}

	//if (m_vTargetPoint.y - 10.f < m_vPosition.y && m_vTargetPoint.y + 10.f > m_vPosition.y
	//	&& m_vTargetPoint.x - 10.f < m_vPosition.x && m_vTargetPoint.x + 10.f > m_vPosition.x)
	if (Vector2::Distance(m_pTarget->GetPosition(), m_vPosition) <= TILECX)
	{
		//m_path.clear();
		m_pRigidBody->SetVelocity(2 * m_fSpeed * (m_vTargetPoint - m_vPosition).Normalize());
		m_ePreState = m_eCurState;
		m_eCurState = STATE::IDLE;
	}
}

void CSlime::SetMotion(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case STATE::IDLE:
			CManagers::instance().Sound()->PlaySound(L"slimeAnticipation.wav", CHANNELID::SOUND_EFFECT3, CManagers::instance().Sound()->GetVolume());
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::ATTACK:		// Jump in this case
			m_tFrame.iFrameStart = 8;
			m_tFrame.iFrameEnd = 19;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::DEAD:
			m_tFrame.iFrameStart = 20;
			m_tFrame.iFrameEnd = 27;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 300;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CSlime::MoveFrame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (STATE::IDLE == m_eCurState)
		{
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
		}
		else if (STATE::ATTACK == m_eCurState)
		{
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
		}
		else if (STATE::DEAD == m_eCurState)
		{
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			{
				CManagers::instance().Event()->DeleteObject(this);
			}
		}

		m_tFrame.dwTime = GetTickCount();
	}
}

void CSlime::OnCollisionEnter(CCollider * _pOther)
{
}

void CSlime::OnCollisionStay(CCollider * _pOther)
{
}

void CSlime::OnCollisionExit(CCollider * _pOther)
{
}
