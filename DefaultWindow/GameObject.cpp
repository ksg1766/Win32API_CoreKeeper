#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject() : m_pCollider(nullptr), m_pRigidBody(nullptr), m_pGraphics(nullptr), m_fSpeed(0.f), m_IsDead(false)
{
}


CGameObject::~CGameObject()
{
}

//void CGameObject::Update_Rect(void)
//{
//	m_tRect.left	= LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
//	m_tRect.top		= LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
//	m_tRect.right	= LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
//	m_tRect.bottom	= LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
//}
