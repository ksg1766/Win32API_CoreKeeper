#include "stdafx.h"
#include "PickAxe.h"
#include "Collider.h"
#include "Graphics.h"
#include "Managers.h"
#include "Player.h"
#include "Monster.h"
#include "Glurch.h"
#include "HiveMother.h"
#include "Cocoon.h"
#include "Wall.h"

CPickAxe::CPickAxe():CItem()
{
	m_IsDead = false;
}


CPickAxe::~CPickAxe()
{
	Release();
}

void CPickAxe::Initialize()
{
	//m_eType = TYPE::ITEM;
	m_eType = TYPE::ITEM;
	m_eItemType = ITEM::WEAPON;

	m_vPosition = m_pOwner->GetPosition() + 10.f * Vector2::Up();
	m_vScale = Vector2(120.f, 120.f);

	m_iDamage = 9;

	m_ePreState = STATE::END;
	m_eCurState = STATE::IDLE;

	m_IsUsing = false;

	m_pCollider = new CCollider;
	m_pGraphics = new CGraphics;

	m_pCollider->Initialize(this);
	m_pCollider->SetScale(m_pOwner->GetScale());

	m_pGraphics->Initialize(this);
	m_pFrameKey = L"PickAxeWood";

	m_eDir = m_pOwner->GetDir();

	m_eRender = RENDERID::GAMEOBJECT;
}

int CPickAxe::Update(void)
{
	m_eDir = m_pOwner->GetDir();
	m_vPosition = m_pOwner->GetPosition() + 10.f * Vector2::Up();
	m_ePreState = m_eCurState;
	m_eCurState = m_pOwner->GetState();

	switch (m_eDir)
	{
	case DIR::RIGHT:
		m_pCollider->SetOffset(Vector2(m_pOwner->GetScale().x, m_pOwner->GetScale().y * 0.3f));
		break;
	case DIR::UP:
		m_pCollider->SetOffset(Vector2(0.f, m_pOwner->GetScale().y * -0.7f));
		break;
	case DIR::DOWN:
		m_pCollider->SetOffset(Vector2(0.f, m_pOwner->GetScale().y * 1.3f));
		break;
	case DIR::LEFT:
		m_pCollider->SetOffset(Vector2(-m_pOwner->GetScale().x, m_pOwner->GetScale().y * 0.3f));
		break;
	}

	return 0;
}

int CPickAxe::LateUpdate(void)
{
	//if (STATE::ATTACK != m_eCurState)
	//{
	//	m_pCollider->SetScale(Vector2::Zero());
	//	//m_pCollider->SetPosition(m_pOwner->GetCollider()->GetPosition());
	//	m_pCollider->SetPosition(Vector2(-100.f, -100.f));
	//}
	//else
	//{
	//	m_pCollider->SetScale(m_pOwner->GetScale());

	//}
	m_pCollider->LateUpdate();
	
	MoveFrame();
	SetMotion();

	return 0;
}

void CPickAxe::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	m_pGraphics->Render(hDC, hMemDC);
	if(m_IsUsing)
		m_pCollider->Render(hDC);
}

void CPickAxe::Release(void)
{
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pGraphics);
}

void CPickAxe::SetMotion(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case STATE::IDLE:
		case STATE::MOVE:
			if(m_IsUsing)			// 여기말고 충돌 검사 끝나고 false로 만들 것
				m_IsUsing = false;
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
		{
			m_tFrame.iFrameStart = m_tFrame.iFrameStartBf;
		}
		m_tFrame.dwTime = GetTickCount();
	}
}

void CPickAxe::Use()
{
}

void CPickAxe::OnCollisionEnter(CCollider * _pOther)
{
	CGameObject* pOtherObj = _pOther->GetHost();
	if (m_IsUsing && (TYPE::MONSTER == pOtherObj->GetType() || TYPE::BOSS == pOtherObj->GetType()))
	{
		CManagers::instance().Pool()->PlayEffect(EFFECT_TYPE::HIT, m_pCollider->GetPosition());
	}
}

void CPickAxe::OnCollisionStay(CCollider * _pOther)
{
	CGameObject* pOtherObj = _pOther->GetHost();
	if (m_IsUsing && m_pOwner->GetWallTarget() == _pOther)
	{
		CManagers::instance().Sound()->PlaySound(L"wall_short.wav", CHANNELID::SOUND_EFFECT12, CManagers::instance().Sound()->GetVolume());
		CManagers::instance().Pool()->PlayEffect(EFFECT_TYPE::HIT, m_pCollider->GetPosition());

		static_cast<CWall*>(pOtherObj)->SetHp(static_cast<CWall*>(pOtherObj)->GetHp() - m_iDamage);
		if (static_cast<CWall*>(pOtherObj)->GetHp() <= 0)
		{
			static_cast<CWall*>(pOtherObj)->DropMaterial();
			CManagers::instance().Event()->DeleteObject(pOtherObj);
		}
	}
	if (m_IsUsing && TYPE::MONSTER == pOtherObj->GetType())
	{
		CManagers::instance().Sound()->PlaySound(L"damage_short.wav", CHANNELID::SOUND_EFFECT2, CManagers::instance().Sound()->GetVolume());
		CManagers::instance().Pool()->PlayEffect(EFFECT_TYPE::HIT, m_pCollider->GetPosition());
		static_cast<CMonster*>(pOtherObj)->SetHp(static_cast<CMonster*>(pOtherObj)->GetHp() - m_iDamage);
	}
	if (m_IsUsing && TYPE::BOSS == pOtherObj->GetType())
	{
		if (BOSS::GLURCH == pOtherObj->GetBossType())
			static_cast<CGlurch*>(pOtherObj)->SetHp(static_cast<CGlurch*>(pOtherObj)->GetHp() - m_iDamage);
		else if (BOSS::HIVEMOTHER == pOtherObj->GetBossType())
			static_cast<CHiveMother*>(pOtherObj)->SetHp(static_cast<CHiveMother*>(pOtherObj)->GetHp() - m_iDamage);
		else
			static_cast<CCocoon*>(pOtherObj)->SetHp(static_cast<CCocoon*>(pOtherObj)->GetHp() - m_iDamage);

		CManagers::instance().Sound()->PlaySound(L"damage_short.wav", CHANNELID::SOUND_EFFECT2, CManagers::instance().Sound()->GetVolume());
		CManagers::instance().Pool()->PlayEffect(EFFECT_TYPE::HIT, m_pCollider->GetPosition());
	}
}

void CPickAxe::OnCollisionExit(CCollider * _pOther)
{
}
