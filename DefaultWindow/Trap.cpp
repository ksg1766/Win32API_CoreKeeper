#include "stdafx.h"
#include "Trap.h"
#include "Player.h"
#include "Managers.h"
#include "Collider.h"
#include "Graphics.h"
#include "Monster.h"
#include "Glurch.h"
#include "HiveMother.h"

CTrap::CTrap()
{
}


CTrap::~CTrap()
{
}

void CTrap::Initialize()
{
	m_eType = TYPE::ITEM;
	m_eItemType = ITEM::CONSUM;

	m_eCurState = STATE::IDLE;
	m_ePreState = STATE::END;

	m_eRender = RENDERID::GAMEOBJECT;

	m_IsDead = false;
	m_IsUsing = false;

	m_vScale = Vector2(48.f, 144.f);
	//m_pOwner = static_cast<CPlayer*>(CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::PLAYER).front());
	m_iRange = (m_vScale.x) / 2.f;

	m_iDamage = 2;
	m_dwTime = 0;

	m_pCollider = new CCollider;
	m_pGraphics = new CGraphics;

	m_pCollider->Initialize(this);
	//m_pCollider->SetOffset(Vector2(0.f, (m_vScale.x) / 2.f));
	m_pGraphics->Initialize(this);

	m_pFrameKey = L"Trap";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 50;
	m_tFrame.dwTime = 0;
}

int CTrap::Update(void)
{
	SetMotion();
	MoveFrame();
	if (1 == m_tFrame.iFrameStart)
		m_IsUsing = true;
	else
		m_IsUsing = false;

	return 0;
}

int CTrap::LateUpdate(void)
{
	m_pCollider->LateUpdate();

	return 0;
}

void CTrap::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	m_pGraphics->Render(hDC, hMemDC);
	m_pCollider->Render(hDC);
}

void CTrap::Release(void)
{
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pGraphics);
}

void CTrap::Use()
{
	CTrap* pTrap = new CTrap;
	pTrap->Initialize();
	pTrap->SetOwner(static_cast<CPlayer*>(CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::PLAYER).front())); // ¤§¤§
	int	i = (m_pOwner->GetPosition().x - (TILECX >> 1)) / TILECX;
	int	j = (m_pOwner->GetPosition().y - (TILECY >> 1)) / TILECY;
	int iIndex = TILEX * j + i;
	//pTrap->SetPosition(Vector2(((m_pOwner->GetPosition().x / TILECX) + 0.5f) * TILECX, ((m_pOwner->GetPosition().x / TILECY) + 0.5f) * TILECY));
	pTrap->SetPosition(CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::TILE)[iIndex]->GetPosition());
	//m_vPosition = Vector2(((m_pOwner->GetPosition() / TILECX) + 0.5f) * TILECX);
	CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::ITEM).push_back(pTrap);
}

void CTrap::OnCollisionEnter(CCollider * _pOther)
{
	CGameObject* pOtherObj = _pOther->GetHost();
	if (STATE::IDLE == m_eCurState && (TYPE::MONSTER == pOtherObj->GetType() || TYPE::BOSS == pOtherObj->GetType()))
	{
		m_ePreState = m_eCurState;
		m_eCurState = STATE::ATTACK;
//		CManagers::instance().Pool()->PlayEffect(EFFECT_TYPE::HIT, m_pCollider->GetPosition());
	}
}

void CTrap::OnCollisionStay(CCollider * _pOther)
{
	CGameObject* pOtherObj = _pOther->GetHost();
	m_ePreState = m_eCurState;
	m_eCurState = STATE::ATTACK;

	if (STATE::ATTACK == m_eCurState && TYPE::MONSTER == pOtherObj->GetType())
	{
		CManagers::instance().Sound()->PlaySound(L"damage_short.wav", CHANNELID::SOUND_EFFECT10, CManagers::instance().Sound()->GetVolume());
	//	CManagers::instance().Pool()->PlayEffect(EFFECT_TYPE::HIT, m_pCollider->GetPosition());
		static_cast<CMonster*>(pOtherObj)->SetHp(static_cast<CMonster*>(pOtherObj)->GetHp() - m_iDamage);
	}
	if (STATE::ATTACK == m_eCurState && TYPE::BOSS == pOtherObj->GetType())
	{
		if (BOSS::GLURCH == pOtherObj->GetBossType())
			static_cast<CGlurch*>(pOtherObj)->SetHp(static_cast<CGlurch*>(pOtherObj)->GetHp() - m_iDamage);
		else if (BOSS::HIVEMOTHER == pOtherObj->GetBossType())
			static_cast<CHiveMother*>(pOtherObj)->SetHp(static_cast<CHiveMother*>(pOtherObj)->GetHp() - m_iDamage);

		CManagers::instance().Sound()->PlaySound(L"damage_short.wav", CHANNELID::SOUND_EFFECT10, CManagers::instance().Sound()->GetVolume());
	//	CManagers::instance().Pool()->PlayEffect(EFFECT_TYPE::HIT, m_pCollider->GetPosition());
	}
//	m_IsUsing = false;
}

void CTrap::SetMotion(void)
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
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case STATE::ATTACK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CTrap::MoveFrame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		if (STATE::ATTACK == m_eCurState && 0 == m_tFrame.iFrameStart)
		{
			if (m_dwTime + 2000 < GetTickCount())
			{
				++m_tFrame.iFrameStart;
				m_dwTime = GetTickCount();
			}
		}
		else
			++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
			m_ePreState = m_eCurState;
			m_eCurState = STATE::IDLE;
		}
		m_tFrame.dwTime = GetTickCount();
	}
}