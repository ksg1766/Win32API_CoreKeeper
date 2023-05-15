#include "stdafx.h"
#include "AcidProjectile.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Graphics.h"
#include "Managers.h"
#include "Player.h"

CAcidProjectile::CAcidProjectile()
{
}


CAcidProjectile::~CAcidProjectile()
{
	Release();
}

void CAcidProjectile::Initialize(void)
{
	m_eType = TYPE::PROJECTILE;
	m_eRender = RENDERID::GAMEOBJECT;
	m_IsDead = false;
	m_eCurState = STATE::IDLE;
	m_eDir = DIR::END;
	m_vPosition = Vector2::Zero();
	m_vScale = Vector2(40.f, 40.f);
	m_fSpeed = 15.f;

	m_iDamage = 10.f;

	m_pCollider = new CCollider;
	m_pRigidBody = new CRigidBody;
	m_pGraphics = new CGraphics;

	m_pCollider->Initialize(this);
	m_pCollider->SetOffset(Vector2::Zero());
	m_pCollider->SetScale(Vector2(200.f, 200.f));
	m_pRigidBody->Initialize(this);
	m_pRigidBody->SetVelocity(m_fSpeed * Vector2::Up());

	m_pGraphics->Initialize(this);


	m_pFrameKey = L"AcidProjectile";
	//m_pFrameKey = L"AcidSplat";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = 0;
	m_tFrame.dwSpeed = 50;

	m_vTargetPoint = CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::PLAYER).front()->GetPosition();
	m_dwTime = GetTickCount();
}

int CAcidProjectile::Update(void)
{
	SetMotion();
	MoveFrame();

	Action();

	m_pRigidBody->Update();

	return 0;
}

int CAcidProjectile::LateUpdate(void)
{
	m_pCollider->LateUpdate();

	return 0;
}

void CAcidProjectile::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	m_pGraphics->Render(hDC, hMemDC);
}

void CAcidProjectile::Release(void)
{
	Safe_Delete(m_pRigidBody);
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pGraphics);
}

void CAcidProjectile::OnCollisionEnter(CCollider * _pOther)
{
	CGameObject* pOtherObj = _pOther->GetHost();
	if (STATE::DEAD == m_eCurState)
	{
		if (TYPE::PLAYER == pOtherObj->GetType())
		{
			static_cast<CPlayer*>(pOtherObj)->SetHp(static_cast<CPlayer*>(pOtherObj)->GetHp() - m_iDamage);

			//-1.f * Vector2(m_vPosition - pOtherObj->GetPosition()).Normalize()
			// hp 감소 & 밀어내기
		}
	}
}

void CAcidProjectile::Action(void)
{
	if (STATE::IDLE == m_eCurState && m_dwTime + 1000 < GetTickCount())
	{
		m_vPosition = Vector2(m_vTargetPoint.x, m_vPosition.y);
		m_pRigidBody->SetVelocity(m_fSpeed * Vector2::Down());
		m_ePreState = m_eCurState;
		m_eCurState = STATE::ATTACK;
	}
	else if (STATE::ATTACK == m_eCurState)
	{
		if (m_vPosition.y >= m_vTargetPoint.y - 5.f)
		{
			Explode();
		}
	}

}

void CAcidProjectile::Explode()
{
	CManagers::instance().Sound()->PlaySound(L"hiveMotherAnticipation.wav", CHANNELID::SOUND_EFFECT9, CManagers::instance().Sound()->GetVolume());
	m_ePreState = m_eCurState;
	m_eCurState = STATE::DEAD;
	m_pFrameKey = L"AcidSplat";
	m_pRigidBody->SetVelocity(Vector2::Zero());
	m_vScale = Vector2(400.f, 400.f);
	CManagers::instance().Scroll()->StartScrollShaking(4);
	//CManagers::instance().Sound()->PlaySound(L".wav", CHANNELID::SOUND_EFFECT6, CManagers::instance().Sound()->GetVolume());

}

void CAcidProjectile::SetMotion(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case STATE::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 30;
			m_tFrame.dwTime = GetTickCount();
		}
		m_ePreState = m_eCurState;
	}
}

void CAcidProjectile::MoveFrame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_eCurState == STATE::DEAD)
		{
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				CManagers::instance().Event()->DeleteObject(this);
		}
		else
		{
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
		}
		m_tFrame.dwTime = GetTickCount();
	}
}
