#include "stdafx.h"
#include "Collider.h"
#include "Managers.h"
#include "GameObject.h"
#include "SelectGDI.h"
#include "Item.h"
#include "Player.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider() : CComponent(), m_iCol(0), m_vOffset(), m_vPosition(), m_vScale()
{
	m_iID = g_iNextID++;
}

CCollider::CCollider(const CCollider & rhs)
{
	m_pHost = nullptr;
	m_vOffset = rhs.m_vOffset;
	m_vScale = rhs.m_vScale;
	m_iID = g_iNextID++;
}

void CCollider::Initialize(CGameObject* _pHost)
{
	m_pHost = _pHost;
	if (TYPE::PLAYER == m_pHost->m_eType || TYPE::MONSTER == m_pHost->m_eType || TYPE::BOSS == m_pHost->m_eType)
	{
		m_vOffset = Vector2(0.f, m_pHost->m_vScale.y * 0.3f);
		m_vPosition = m_pHost->m_vPosition + m_vOffset;
		m_vScale = Vector2(m_pHost->m_vScale.x * 0.5f, m_pHost->m_vScale.y * 0.5f);
	}
	// 나눌 필요가 있는지 의문
	else if (TYPE::ITEM == m_pHost->m_eType)
	{
		if (ITEM::WEAPON == dynamic_cast<CItem*>(m_pHost)->GetItemType())
		{
			m_vOffset = Vector2::Zero();
			m_vPosition = dynamic_cast<CItem*>(m_pHost)->GetOwner()->m_vPosition + m_vOffset;
			m_vScale = dynamic_cast<CItem*>(m_pHost)->GetOwner()->m_vScale;
		}
	}

	else if (TYPE::WALL == m_pHost->m_eType)
	{
		m_vPosition = m_pHost->m_vPosition;
		m_vScale = Vector2(m_pHost->m_vScale.x, m_pHost->m_vScale.y);
	}
}


void CCollider::LateUpdate()
{
	assert(0 <= m_iCol);
	// Weapon 같은 경우 플레이어의 m_eDir과 같은 방향으로 Collider On/Off
	// 플레이어 앞 3타일 // 방향 얻어와서 켜는것으로 결정
	if (TYPE::ITEM == m_pHost->m_eType)
	{
		/*CPlayer* pOwner = dynamic_cast<CItem*>(m_pHost)->GetOwner();
		
		switch (pOwner->m_eDir)
		{ 
		case DIR::RIGHT:
			m_vOffset = Vector2(pOwner->m_vScale.x, pOwner->m_vScale.y * 0.3f);
			break;
		case DIR::UP:
			m_vOffset = Vector2(0.f, pOwner->m_vScale.y * -0.7f);
			break;
		case DIR::DOWN:
			m_vOffset = Vector2(0.f, pOwner->m_vScale.y * 1.3f);
			break;
		case DIR::LEFT:
			m_vOffset = Vector2(-pOwner->m_vScale.x, pOwner->m_vScale.y * 0.3f);
			break;
		}*/
	}	m_vPosition = m_pHost->m_vPosition + m_vOffset;
		
	/*}
	else
	{
		m_vPosition = m_pHost->m_vPosition + m_vOffset;
	}*/
}

void CCollider::Render(HDC _hDC)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (m_iCol)
		ePen = PEN_TYPE::RED;

	CSelectGDI temp1(_hDC, ePen);
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

//void CCollider::SetThisRay()
//{
//	m_vScale = Vector2(m_pHost->m_vScale.x, 1.f);
//	m_vOffset = Vector2(m_pHost->m_pCollider->m_vScale.x, m_pHost->m_pCollider->m_vScale.y * 0.7f);
//	m_vPosition = Vector2(m_pHost->m_vPosition + m_vOffset);
//}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	//
	//if (_pOther->m_isRay && TYPE::PLAYER == _pOther->m_pHost->m_eType)
 	//	dynamic_cast<CPlayer*>(_pOther)->SetWallTarget(this);

	++m_iCol;
	m_pHost->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionStay(CCollider* _pOther)
{
	m_pHost->OnCollisionStay(_pOther);
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--m_iCol;
	m_pHost->OnCollisionExit(_pOther);
}


CCollider::~CCollider()
{
}