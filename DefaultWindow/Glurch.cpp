#include "stdafx.h"
#include "Glurch.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Graphics.h"
#include "Shadow.h"
#include "Player.h"
#include "HP_Bar_Boss.h"
#include "Managers.h"
#include "Statue_Glurch.h"
#include "GameScene.h"

CGlurch::CGlurch()
{
}

CGlurch::~CGlurch()
{
	Release();
}

void CGlurch::Initialize(void)
{
	m_IsDead = false;
	m_eType = TYPE::BOSS;
	m_eBossType = BOSS::GLURCH;
	m_vPosition = Vector2(63.5f * TILECX, 42.5f * TILECY);
	m_vScale = Vector2(384.f, 384.f);
	m_iRange = 7 * TILECX;

	m_iBiom = 0;

	m_iMaxHp = 150;
	m_iHp = m_iMaxHp;

	m_pHPBar = new CHP_Bar_Boss;
	static_cast<CHP_Bar_Boss*>(m_pHPBar)->SetHost(this);
	static_cast<CHP_Bar_Boss*>(m_pHPBar)->Initialize();
	//static_cast<CHP_Bar_Boss*>(m_pHPBar)->SetUIType();
	CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::UI).push_back(m_pHPBar);

	m_iDamage = 20;

	m_vTargetPoint = m_vPosition;
	m_pTarget = nullptr;
	m_IsTakingDown = false;
	m_ePreState = STATE::END;
	m_eCurState = STATE::IDLE;

	m_pShadow = new CShadow;
	m_pCollider = new CCollider;
	m_pRigidBody = new CRigidBody;
	m_pGraphics = new CGraphics;

	m_pShadow->SetHost(this);
	m_pShadow->Initialize();
	m_pShadow->SetScale(Vector2(216.f, 144.f));
	m_pShadow->SetFrameKey(L"Glurch_Shadow");

	m_pCollider->Initialize(this);
	m_pRigidBody->Initialize(this);
	m_pGraphics->Initialize(this);

	m_fSpeed = 8.f;

	m_dwTime = 0;

	m_pFrameKey = L"Glurch";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDERID::GAMEOBJECT;
}

int CGlurch::Update(void)
{
	if (m_iHp <= 0)
	{
		m_iHp = 0;
		m_fSpeed = 0;
		m_eCurState = STATE::DEAD;
		m_pFrameKey = L"SlimeExplosion";

		m_vScale = Vector2(420.f, 420.f);

		CManagers::instance().Sound()->PlaySound(L"slimeBossDeath.wav", CHANNELID::SOUND_EFFECT8, CManagers::instance().Sound()->GetVolume());
		m_pShadow->SetScale(Vector2::Zero());
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
		if(STATE::IDLE == m_eCurState)
			m_vTargetPoint = m_pTarget->GetPosition();
		if(STATE::ATTACK != m_eCurState)
			m_eCurState = STATE::MOVE;
	}
	else
	{
		m_vTargetPoint = m_vPosition;
		m_eCurState = STATE::IDLE;
	}

	Action();

	m_pRigidBody->Update();
	static_cast<CHP_Bar_Boss*>(m_pHPBar)->Update();
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

	m_pShadow->Render(hDC);
	m_pGraphics->Render(hDC, hMemDC);
	m_pCollider->Render(hDC);

	m_pHPBar->Render(hDC);
}

void CGlurch::Release(void)
{
	Safe_Delete(m_pShadow);
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pRigidBody);
	Safe_Delete(m_pGraphics);

	CManagers::instance().Event()->DeleteObject(m_pHPBar);
}

void CGlurch::Action()
{
	switch (m_eCurState)
	{
	case STATE::IDLE:
		m_pRigidBody->SetVelocity(Vector2::Zero());
		m_pShadow->SetPosition(m_vPosition + Vector2::Down() * 45.f);//
		break;

	case STATE::MOVE:	//m_tFrame.iFrameStart 가 특정 프레임이 되었을 때 움직임
		m_pShadow->SetPosition(Vector2(m_vPosition + Vector2::Down() * 45.f));
		if (14 == m_tFrame.iFrameStart)
		{
			m_pRigidBody->SetVelocity(m_fSpeed * (m_vTargetPoint + 100.f * Vector2::Up() - m_vPosition).Normalize());
			m_pShadow->SetPosition(Vector2(m_vPosition.x, m_vPosition.y + 100.f));
		}
		if (m_vTargetPoint.y - 70.f > m_vPosition.y && m_vTargetPoint.y - 130.f < m_vPosition.y
			&& m_vTargetPoint.x - 30.f < m_vPosition.x && m_vTargetPoint.x +30.f > m_vPosition.x)
		{	
			m_pRigidBody->SetVelocity(Vector2::Zero());
			m_ePreState = m_eCurState;
			m_eCurState = STATE::ATTACK;
		}
		break;

	case STATE::ATTACK:
//		m_pRigidBody->SetVelocity(Vector2(0.f, m_fSpeed));
		TakeDown();
		break;
	}
}

void CGlurch::TakeDown()
{
	if (m_vPosition.y > m_vTargetPoint.y - 20.f && m_vPosition.y < m_vTargetPoint.y + 20.f)	// TargetPoint에 도달 했을 시
	{
		m_IsTakingDown = false;
		CManagers::instance().Sound()->PlaySound(L"SlimeBossImpact_short.wav", CHANNELID::SOUND_EFFECT6, CManagers::instance().Sound()->GetVolume());
		m_pRigidBody->SetVelocity(Vector2::Zero());
		
		CManagers::instance().Scroll()->StartScrollShaking(6);
		m_eCurState = STATE::IDLE;
	}
	else
	{
		if (m_dwTime + 10000 / m_fSpeed < GetTickCount())
		{
			m_IsTakingDown = true;
			m_dwTime = GetTickCount();
		}
		m_pRigidBody->SetVelocity(m_fSpeed * Vector2::Down());
		m_pShadow->SetPosition(Vector2(m_vPosition.x, m_vTargetPoint.y));
	}
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
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::MOVE:		// Jump in this case
			m_tFrame.iFrameStart = 8;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameEnd;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::ATTACK:		// Take down in this case
			m_tFrame.iFrameStart = 16;
			m_tFrame.iFrameEnd = 18;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;	// ?????????????????????????
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
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
		else if (STATE::ATTACK == m_eCurState)
		{
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
		}
		else if (STATE::DEAD == m_eCurState)
		{// 아직 테스트 안해봄
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			{
				m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
				CManagers::instance().Event()->DeleteObject(this);
				static_cast<CGameScene*>(CManagers::instance().Scene()->CurrentScene())->SetGlurchDead(true);
			}
		}
		m_tFrame.dwTime = GetTickCount();
	}
}

void CGlurch::OnCollisionEnter(CCollider * _pOther)
{
	//CGameObject* pOtherObj = _pOther->GetHost();
	//if (m_IsTakingDown)
	//{
	//	if (TYPE::PLAYER == pOtherObj->GetType())
	//	{
	//		// hp 감소 & 밀어내기
	//	}
	//	else if (TYPE::WALL == pOtherObj->GetType())
	//	{
	//		CManagers::instance().Event()->DeleteObject(pOtherObj);
	//	}
	//}

	CGameObject* pOtherObj = _pOther->GetHost();
	if (STATE::MOVE != m_eCurState)
	{
		if (TYPE::PLAYER == pOtherObj->GetType() || TYPE::MONSTER == pOtherObj->GetType())
		{
			Vector2 vOtherPos = _pOther->GetPosition();
			Vector2 vOtherScale = _pOther->GetScale();

			Vector2 vThisPos = GetCollider()->GetPosition();
			Vector2 vThisScale = GetCollider()->GetScale();

			float fWidth = fabs(vOtherPos.x - vThisPos.x);
			float fHeight = fabs(vOtherPos.y - vThisPos.y);
			float fRadiusX = (vOtherScale.x / 2.f + vThisScale.x / 2.f) - fWidth;
			float fRadiusY = (vOtherScale.y / 2.f + vThisScale.y / 2.f) - fHeight;

			if (fRadiusX < fRadiusY)
			{
				if (vOtherPos.x < vThisPos.x)
				{
					vOtherPos = pOtherObj->GetPosition();
					vOtherPos.x -= fRadiusX;
				}
				else
				{
					vOtherPos = pOtherObj->GetPosition();
					vOtherPos.x += fRadiusX;
				}
			}
			else
			{
				if (vOtherPos.y < vThisPos.y)
				{
					vOtherPos = pOtherObj->GetPosition();
					vOtherPos.y -= fRadiusY;
				}
				else
				{
					vOtherPos = pOtherObj->GetPosition();
					vOtherPos.y += fRadiusY;
				}
			}
			pOtherObj->SetPosition(vOtherPos);
	 	}
	}

	if (m_IsTakingDown)
	{
		if (TYPE::PLAYER == pOtherObj->GetType())
		{
			CManagers::instance().Sound()->PlaySound(L"damagePlayer.wav", CHANNELID::SOUND_EFFECT8, CManagers::instance().Sound()->GetVolume());
			static_cast<CPlayer*>(pOtherObj)->SetHp(static_cast<CPlayer*>(pOtherObj)->GetHp() - m_iDamage);

			//-1.f * Vector2(m_vPosition - pOtherObj->GetPosition()).Normalize()
			// hp 감소 & 밀어내기
		}
		else if (TYPE::WALL == pOtherObj->GetType())
		{
			CManagers::instance().Event()->DeleteObject(pOtherObj);
		}
	}
}

void CGlurch::OnCollisionStay(CCollider * _pOther)
{
	CGameObject* pOtherObj = _pOther->GetHost();
	if (STATE::MOVE != m_eCurState)
	{
		if (TYPE::PLAYER == pOtherObj->GetType() || TYPE::MONSTER == pOtherObj->GetType())
		{
			Vector2 vOtherPos = _pOther->GetPosition();
			Vector2 vOtherScale = _pOther->GetScale();

			Vector2 vThisPos = GetCollider()->GetPosition();
			Vector2 vThisScale = GetCollider()->GetScale();

			float fWidth = fabs(vOtherPos.x - vThisPos.x);
			float fHeight = fabs(vOtherPos.y - vThisPos.y);
			float fRadiusX = (vOtherScale.x / 2.f + vThisScale.x / 2.f) - fWidth;
			float fRadiusY = (vOtherScale.y / 2.f + vThisScale.y / 2.f) - fHeight;

			if (fRadiusX < fRadiusY)
			{
				if (vOtherPos.x < vThisPos.x)
				{
					vOtherPos = pOtherObj->GetPosition();
					vOtherPos.x -= fRadiusX;
				}
				else
				{
					vOtherPos = pOtherObj->GetPosition();
					vOtherPos.x += fRadiusX;
				}
			}
			else
			{
				if (vOtherPos.y < vThisPos.y)
				{
					vOtherPos = pOtherObj->GetPosition();
					vOtherPos.y -= fRadiusY;
				}
				else
				{
					vOtherPos = pOtherObj->GetPosition();
					vOtherPos.y += fRadiusY;
				}
			}
			pOtherObj->SetPosition(vOtherPos);
		}
	}
}

void CGlurch::OnCollisionExit(CCollider * _pOther)
{
}