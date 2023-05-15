#include "stdafx.h"
#include "Larva.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Graphics.h"
#include "Shadow.h"
#include "Managers.h"

CLarva::CLarva()
{
}


CLarva::~CLarva()
{
	Release();
}

void CLarva::Initialize(void)
{
	m_IsDead = true;
	m_eType = TYPE::MONSTER;
	//m_vPosition = Vector2(600.f, 700.f);
	m_eDir = DIR::RIGHT;
	//m_eDir = (DIR)(GetTickCount() % 8 / 2);// DIR::RIGHT;

	m_iBiom = 2;

	m_iHp = 30;
	m_iDamage = 7;

	m_vScale = Vector2(32.f, 32.f);
	m_iRange = 7 * TILECX;

	m_vTargetPoint = m_vPosition;
	m_pTarget = nullptr;
	m_ePreState = STATE::END;
	m_eCurState = STATE::IDLE;

	m_pCollider = new CCollider;
	m_pRigidBody = new CRigidBody;
	m_pGraphics = new CGraphics;

	m_pCollider->Initialize(this);
	m_pRigidBody->Initialize(this);
	m_pGraphics->Initialize(this);
	
	m_pShadow = new CShadow;

	m_pShadow->SetHost(this);
	m_pShadow->Initialize();
	m_pShadow->SetScale(Vector2(32.f, 8.f));//
	m_pShadow->SetFrameKey(L"Larva_Shadow");//

	FRAME _tShadowFrame;
	_tShadowFrame.iFrameStart = 0;
	_tShadowFrame.iFrameStartBf = _tShadowFrame.iFrameStart;
	_tShadowFrame.iFrameEnd = 0;
	_tShadowFrame.iMotion = 0;
	_tShadowFrame.dwSpeed = 100;
	_tShadowFrame.dwTime = GetTickCount();
	m_pShadow->SetFrame(_tShadowFrame);

	m_fSpeed = 1.f;

	m_dwTime = 0;

	m_pFrameKey = L"Larva";
	
	m_eRender = RENDERID::GAMEOBJECT;
}

int CLarva::Update(void)
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
	}

	if (nullptr != m_pTarget)
	{
		if (STATE::IDLE == m_eCurState)
		{
			m_vTargetPoint = m_pTarget->GetPosition();
			m_pRigidBody->SetVelocity(m_fSpeed * (m_vTargetPoint - m_vPosition).Normalize());
			if(Vector2::Distance(pPlayer->GetPosition(), m_vPosition) <= TILECX)
				m_eCurState = STATE::ATTACK;
		}
	}
	else
	{
		m_pRigidBody->SetVelocity(Vector2::Zero());	//
		m_vTargetPoint = m_vPosition;
		m_eCurState = STATE::IDLE;
	}

	Action();

	m_pRigidBody->Update();

	return 0;
}

int CLarva::LateUpdate(void)
{
	if (STATE::DEAD != m_eCurState)
		m_pCollider->LateUpdate();

	MoveFrame();
	SetMotion();

	return 0;
}

void CLarva::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	m_pShadow->Render(hDC);
	m_pGraphics->Render(hDC, hMemDC);

	if (STATE::DEAD != m_eCurState)
		m_pCollider->Render(hDC);
}

void CLarva::Release(void)
{
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pRigidBody);
	Safe_Delete(m_pGraphics);
	Safe_Delete(m_pShadow);
}

void CLarva::Action()
{
	switch (m_eCurState)
	{
	case STATE::IDLE: // 라바도 IDLE이 움직임 포함
		//m_pRigidBody->SetVelocity(Vector2::Zero());
		m_pShadow->SetPosition(Vector2(m_vPosition.x, m_vPosition.y + 10.f));
		
		if (m_pRigidBody->GetVelocity().x - m_pRigidBody->GetVelocity().y >= 0)
		{
			if (m_pRigidBody->GetVelocity().x >= 0)
				m_eDir = DIR::RIGHT;
			else
				m_eDir = DIR::UP;
		}
		else
		{
			if (m_pRigidBody->GetVelocity().y >= 0)
				m_eDir = DIR::DOWN;
			else
				m_eDir = DIR::LEFT;
		}
		break;

	case STATE::ATTACK:
		m_pShadow->SetPosition(Vector2(m_vPosition.x, m_vPosition.y + 10.f));
		Attack();
		break;
	}
}

void CLarva::Attack()
{
	CManagers::instance().Sound()->PlaySound(L"larvaAttack.wav", CHANNELID::SOUND_EFFECT4, CManagers::instance().Sound()->GetVolume());
	if (m_pRigidBody->GetVelocity().x - m_pRigidBody->GetVelocity().y >= 0)
	{
		if (m_pRigidBody->GetVelocity().x >= 0)
			m_eDir = DIR::RIGHT;
		else
			m_eDir = DIR::UP;
	}
	else
	{
		if (m_pRigidBody->GetVelocity().y >= 0)
			m_eDir = DIR::DOWN;
		else
			m_eDir = DIR::LEFT;
	}

	if (m_vTargetPoint.y - 10.f < m_vPosition.y && m_vTargetPoint.y + 10.f > m_vPosition.y
		&& m_vTargetPoint.x - 10.f < m_vPosition.x && m_vTargetPoint.x + 10.f > m_vPosition.x)
	{

		//m_pRigidBody->SetVelocity(Vector2::Zero());
		//m_ePreState = m_eCurState;
		m_eCurState = STATE::IDLE;
	}
}

void CLarva::SetMotion(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case STATE::IDLE:
			if (m_eDir == DIR::RIGHT)
			{
				m_tFrame.iFrameStart = 8;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 11;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::UP)
			{
				m_tFrame.iFrameStart = 16;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 19;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::LEFT)
			{
				m_tFrame.iFrameStart = 12;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 15;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::DOWN)
			{
				m_tFrame.iFrameStart = 4;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 7;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
			}
			break;
		case STATE::ATTACK:		// Jump in this case
			if (m_eDir == DIR::RIGHT)
			{
				m_tFrame.iFrameStart = 24;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 27;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::UP)
			{
				m_tFrame.iFrameStart = 32;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 35;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::LEFT)
			{
				m_tFrame.iFrameStart = 28;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 31;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
			}
			else if (m_eDir == DIR::DOWN)
			{
				m_tFrame.iFrameStart = 20;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 23;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 100;
				m_tFrame.dwTime = GetTickCount();
			}
			break;
		case STATE::DEAD:
			{
				m_tFrame.iFrameStart = 36;
				m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
				m_tFrame.iFrameEnd = 39;
				m_tFrame.iMotion = 0;
				m_tFrame.dwSpeed = 300;
				m_tFrame.dwTime = GetTickCount();

			}
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CLarva::MoveFrame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
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

		m_tFrame.dwTime = GetTickCount();
	}
}
