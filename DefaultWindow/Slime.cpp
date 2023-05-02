#include "stdafx.h"
#include "Slime.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Graphics.h"
#include "Managers.h"

CSlime::CSlime()
{
}


CSlime::~CSlime()
{
}

void CSlime::Initialize(void)
{
	m_IsDead = false;
	m_eType = TYPE::BOSS;
	m_vPosition = Vector2(900.f, 900.f);
	m_vScale = Vector2(256.f, 256.f);
	m_iRange = 7 * TILECX;

	m_pTarget = nullptr;
	m_ePreState = STATE::END;
	m_eCurState = STATE::IDLE;

	m_pCollider = new CCollider;
	m_pRigidBody = new CRigidBody;
	m_pGraphics = new CGraphics;

	m_pCollider->Initialize(this);
	m_pRigidBody->Initialize(this);
	m_pGraphics->Initialize(this);

	m_fSpeed = 30.f;

	m_fTime = 0;

	m_pFrameKey = L"Slime";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	m_eRender = RENDERID::GAMEOBJECT;
}

int CSlime::Update(void)
{
	return 0;
}

int CSlime::LateUpdate(void)
{
	return 0;
}

void CSlime::Render(HDC hDC)
{
}

void CSlime::Release(void)
{
}
