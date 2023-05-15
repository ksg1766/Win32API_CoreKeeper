#include "stdafx.h"
#include "Ray.h"
#include "Collider.h"
#include "Graphics.h"
#include "Player.h"

CRay::CRay():m_pHost(nullptr)
{
	m_IsDead = false;
}


CRay::~CRay()
{
	Release();
}

void CRay::Initialize(void)
{
	m_pCollider = new CCollider;
	//m_pCollider->Initialize(this);
	m_pCollider->SetHost(this);
	m_eType = TYPE::RAY;	// 임시 타입

	m_vScale = Vector2(m_pHost->GetScale().x, 1.f);
	m_vOffset = Vector2(m_pHost->GetCollider()->GetScale().x, m_pHost->GetCollider()->GetScale().y * 0.7f);
	m_vPosition = Vector2(m_pHost->GetPosition() + m_vOffset);

	m_eRender = RENDERID::GAMEOBJECT;
}

int CRay::Update(void)
{
	m_eDir = m_pHost->GetDir();

	if (DIR::RIGHT == m_eDir)
	{
		m_vScale = Vector2(m_pHost->GetScale().x, 1.f);
		m_vOffset = Vector2(m_pHost->GetCollider()->GetScale().x, m_pHost->GetCollider()->GetScale().y * 0.7f);
	}
	else if (DIR::UP == m_eDir)
	{
		m_vScale = Vector2(1.f, m_pHost->GetScale().y);
		m_vOffset = Vector2(0.f, m_pHost->GetCollider()->GetScale().y * -0.3f);
	}
	else if (DIR::LEFT == m_eDir)
	{
		m_vScale = Vector2(m_pHost->GetScale().x, 1.f);
		m_vOffset = Vector2(-m_pHost->GetCollider()->GetScale().x, m_pHost->GetCollider()->GetScale().y * 0.7f);
	}
	else if (DIR::DOWN == m_eDir)
	{
		m_vScale = Vector2(1.f, m_pHost->GetScale().y);
		m_vOffset = Vector2(0.f, m_pHost->GetCollider()->GetScale().y * 1.7f);
	}
	m_vPosition = Vector2(m_pHost->GetPosition() + m_vOffset);

	m_pCollider->SetScale(m_vScale);

	return 0;
}

int CRay::LateUpdate(void)
{
	m_pCollider->LateUpdate();
	return 0;
}

void CRay::Render(HDC hDC)
{
	m_pCollider->Render(hDC);
}

void CRay::Release(void)
{
	Safe_Delete(m_pCollider);
}

void CRay::SetHost(CGameObject * _pHost)
{
	m_pHost = _pHost;
}

void CRay::OnCollisionEnter(CCollider * _pOther)
{
	if (TYPE::PLAYER == m_pHost->GetType() && TYPE::WALL == _pOther->GetHost()->GetType())
		static_cast<CPlayer*>(m_pHost)->SetWallTarget(_pOther);
}

void CRay::OnCollisionStay(CCollider * _pOther)
{
}

void CRay::OnCollisionExit(CCollider * _pOther)
{
	if (TYPE::PLAYER == m_pHost->GetType())
		static_cast<CPlayer*>(m_pHost)->SetWallTarget(nullptr);
	
}
