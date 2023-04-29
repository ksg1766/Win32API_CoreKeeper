#include "stdafx.h"
#include "Collider.h"
//#include "Managers.h"
#include "GameObject.h"
#include "SelectGDI.h"
#include "Item.h"
#include "Player.h"

CCollider::CCollider() : CComponent(), m_iCol(0), m_vOffeset(), m_vPosition(), m_vScale()
{
}

void CCollider::Initialize(CGameObject* _pHost)
{
	m_pHost = _pHost;
	if (TYPE::PLAYER == m_pHost->GetType() || TYPE::MONSTER == m_pHost->GetType() || TYPE::BOSS == m_pHost->GetType())
	{
		m_vOffeset = Vector2(0.f, m_pHost->GetScale().y * 0.3f);
		m_vPosition = m_pHost->GetPosition() + m_vOffeset;
		m_vScale = Vector2(m_pHost->GetScale().x * 0.5f, m_pHost->GetScale().y * 0.4f);
	}
	// 나눌 필요가 있는지 의문
	else if (TYPE::ITEM == m_pHost->GetType())
	{
		if (ITEM::WEAPON == dynamic_cast<CItem*>(m_pHost)->GetItemType())
		{
			m_vOffeset = Vector2::Zero();
			m_vPosition = dynamic_cast<CItem*>(m_pHost)->GetOwner()->GetPosition() + m_vOffeset;
			m_vScale = dynamic_cast<CItem*>(m_pHost)->GetOwner()->GetScale();
			//m_vScale = Vector2(66.f * 3.f, 66.f);
		}
	}
}


void CCollider::LateUpdate()
{
	// Weapon 같은 경우 플레이어의 m_eDir과 같은 방향으로 Collider On/Off
	// 플레이어 앞 3타일 // 방향 얻어와서 켜는것으로 결정
	if (TYPE::ITEM == m_pHost->GetType())
	{
		CPlayer* pOwner = dynamic_cast<CItem*>(m_pHost)->GetOwner();

		switch (pOwner->GetDir())
		{
		case DIR::RIGHT:
			m_vPosition = Vector2(pOwner->GetPosition().x + pOwner->GetScale().x, pOwner->GetPosition().y);
			break;
		case DIR::UP:
			m_vPosition = Vector2(pOwner->GetPosition().x, pOwner->GetPosition().y - pOwner->GetScale().y);
			break;
		case DIR::DOWN:
			m_vPosition = Vector2(pOwner->GetPosition().x, pOwner->GetPosition().y + pOwner->GetScale().y);
			break;
		case DIR::LEFT:
			m_vPosition = Vector2(pOwner->GetPosition().x - pOwner->GetScale().x, pOwner->GetPosition().y);
			break;
		}
	}
	else
		m_vPosition = m_pHost->GetPosition() + m_vOffeset;
}

void CCollider::Render(HDC _hDC)
{
	CSelectGDI temp1(_hDC, PEN_TYPE::GREEN);
	CSelectGDI temp2(_hDC, BRUSH_TYPE::HOLLOW);

	Rectangle(_hDC,
		(int)(m_vPosition.x - m_vScale.x / 2.f),
		(int)(m_vPosition.y - m_vScale.y / 2.f),
		(int)(m_vPosition.x + m_vScale.x / 2.f),
		(int)(m_vPosition.y + m_vScale.y / 2.f)
	);
}

void CCollider::OnCollisionEnter()
{
}

void CCollider::OnCollisionStay()
{
}

void CCollider::OnCollisionExit()
{
}


CCollider::~CCollider()
{
}