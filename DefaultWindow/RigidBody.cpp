#include "stdafx.h"
#include "RigidBody.h"
#include "GameObject.h"

CRigidBody::CRigidBody(): CComponent(), m_vVelocity()
{
}

void CRigidBody::Initialize(CGameObject* _pHost)
{
	m_pHost = _pHost;

}

void CRigidBody::Update()
{
	Move();
}

void CRigidBody::Move()
{
	m_pHost->SetPosition(m_pHost->GetPosition() + m_vVelocity);
}

CRigidBody::~CRigidBody()
{
}
