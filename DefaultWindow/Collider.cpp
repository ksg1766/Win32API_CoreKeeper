#include "stdafx.h"
#include "Collider.h"
#include "Managers.h"
#include "GameObject.h"
#include "SelectGDI.h"
#include "Item.h"
#include "Player.h"

CCollider::CCollider() : CComponent(), m_iCol(0), m_vOffset(), m_vPosition(), m_vScale()
{
}

void CCollider::Initialize(CGameObject* _pHost)
{
	m_pHost = _pHost;
	if (TYPE::PLAYER == m_pHost->GetType() || TYPE::MONSTER == m_pHost->GetType() || TYPE::BOSS == m_pHost->GetType())
	{
		m_vOffset = Vector2(0.f, m_pHost->GetScale().y * 0.3f);
		m_vPosition = m_pHost->GetPosition() + m_vOffset;
		m_vScale = Vector2(m_pHost->GetScale().x * 0.5f, m_pHost->GetScale().y * 0.4f);
	}
	// ���� �ʿ䰡 �ִ��� �ǹ�
	else if (TYPE::ITEM == m_pHost->GetType())
	{
		if (ITEM::WEAPON == dynamic_cast<CItem*>(m_pHost)->GetItemType())
		{
			m_vOffset = Vector2::Zero();
			m_vPosition = dynamic_cast<CItem*>(m_pHost)->GetOwner()->GetPosition() + m_vOffset;
			m_vScale = dynamic_cast<CItem*>(m_pHost)->GetOwner()->GetScale();
			//m_vScale = Vector2(66.f * 3.f, 66.f);
		}
	}

	else if (TYPE::WALL == m_pHost->GetType())
	{
		m_vPosition = m_pHost->GetPosition();
		m_vScale = Vector2(m_pHost->GetScale().x, m_pHost->GetScale().y);
	}
}


void CCollider::LateUpdate()
{
	// Weapon ���� ��� �÷��̾��� m_eDir�� ���� �������� Collider On/Off
	// �÷��̾� �� 3Ÿ�� // ���� ���ͼ� �Ѵ°����� ����
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
		m_vPosition = m_pHost->GetPosition() + m_vOffset;
}

void CCollider::Render(HDC _hDC)
{
	CSelectGDI temp1(_hDC, PEN_TYPE::GREEN);
	CSelectGDI temp2(_hDC, BRUSH_TYPE::HOLLOW);

	float	fScrollX = CManagers::instance().Scroll()->Get_ScrollX();
	float	fScrollY = CManagers::instance().Scroll()->Get_ScrollY();

	Rectangle(_hDC,
		(int)(m_vPosition.x - m_vScale.x / 2.f + fScrollX),
		(int)(m_vPosition.y - m_vScale.y / 2.f + fScrollY),
		(int)(m_vPosition.x + m_vScale.x / 2.f + fScrollX),
		(int)(m_vPosition.y + m_vScale.y / 2.f + fScrollY)
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