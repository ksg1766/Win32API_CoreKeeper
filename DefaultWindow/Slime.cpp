#include "stdafx.h"
#include "Slime.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Graphics.h"
#include "Shadow.h"
#include "Managers.h"

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

	m_vScale = Vector2(64.f, 64.f);
	m_iRange = 3 * TILECX;

	m_vTargetPoint = m_vPosition;
	m_pTarget = nullptr;
	m_ePreState = STATE::END;
	m_eCurState = STATE::IDLE;

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

	m_fSpeed = 10.f;

	m_fTime = 0;

	m_pFrameKey = L"Slime";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDERID::GAMEOBJECT;
}

int CSlime::Update(void)
{
	CGameObject* pPlayer = CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::PLAYER).front();
	if (Vector2::Distance(pPlayer->GetPosition(), m_vPosition) <= m_iRange)
	{
		m_pTarget = pPlayer;
	}
	else
	{
		m_pTarget = nullptr;
	}

	if (nullptr != m_pTarget)
	{
		if (STATE::IDLE == m_eCurState)
		{
			m_vTargetPoint = m_pTarget->GetPosition();
			m_eCurState = STATE::ATTACK;
		}
	}
	else
	{
		m_vTargetPoint = m_vPosition;
		m_eCurState = STATE::IDLE;
	}

	Action();

	m_pRigidBody->Update();

	return 0;
}

int CSlime::LateUpdate(void)
{
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
		m_pRigidBody->SetVelocity(Vector2::Zero());
		m_pShadow->SetPosition(Vector2(m_vPosition.x, m_vPosition.y + 10.f));
		break;

	case STATE::ATTACK:
		m_pShadow->SetPosition(Vector2(m_vPosition.x, m_vPosition.y + 10.f));
		Attack();
		break;
	}
}

void CSlime::Attack()
{
	m_pShadow->SetPosition(Vector2(m_vPosition.x, m_vPosition.y + 10.f));
	if (16 == m_tFrame.iFrameStart)
	{
		m_pRigidBody->SetVelocity(m_fSpeed * (m_vTargetPoint - m_vPosition).Normalize());
	}
	if (m_vTargetPoint.y - 10.f < m_vPosition.y && m_vTargetPoint.y + 10.f > m_vPosition.y
		&& m_vTargetPoint.x - 10.f < m_vPosition.x && m_vTargetPoint.x + 10.f > m_vPosition.x)
	{
		m_pRigidBody->SetVelocity(Vector2::Zero());
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
		else
		{
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
		}

		m_tFrame.dwTime = GetTickCount();
	}
}
