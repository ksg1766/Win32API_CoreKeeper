#include "stdafx.h"
#include "Statue_HiveMother.h"
#include "Collider.h"
#include "Graphics.h"
#include "Managers.h"
#include "GameScene.h"

CStatue_HiveMother::CStatue_HiveMother()
{
}


CStatue_HiveMother::~CStatue_HiveMother()
{
}

void CStatue_HiveMother::Initialize(void)
{
	m_eType = TYPE::WALL;
	m_eRender = RENDERID::GAMEOBJECT;
	m_IsDead = false;
	m_vPosition = Vector2(17 * TILECX, 10 * TILECY);
	m_vScale = Vector2(144.f, 189.f);

	m_iHp = INT32_MAX;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = 0;
	m_tFrame.dwSpeed = 300;

	m_pFrameKey = L"Statue_HiveMother";
	m_dwTime = 0;
	m_fSpeed = 0.f;

	m_pCollider = new CCollider;
	m_pGraphics = new CGraphics;

	m_pCollider->Initialize(this);
	m_pGraphics->Initialize(this);
}

int CStatue_HiveMother::Update(void)
{
	//SetMotion();
	//MoveFrame();

	return 0;
}

int CStatue_HiveMother::LateUpdate(void)
{
	m_pCollider->LateUpdate();

	return 0;
}

void CStatue_HiveMother::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	MoveFrame();
	m_pGraphics->Render(hDC, hMemDC);
	m_pCollider->Render(hDC);
}

void CStatue_HiveMother::Release(void)
{
	Safe_Delete(m_pGraphics);
	Safe_Delete(m_pCollider);
}

void CStatue_HiveMother::OnCollisionStay(CCollider * _pOther)
{
	__super::OnCollisionStay(_pOther);

	CGameObject* pOtherObj = _pOther->GetHost();
	if (TYPE::PLAYER == pOtherObj->GetType())
		if (CManagers::instance().Key()->Key_Down('G'))
			if (static_cast<CGameScene*>(CManagers::instance().Scene()->CurrentScene())->GetHiveMotherDead())
				m_tFrame.iFrameEnd = 2;
}

void CStatue_HiveMother::SetMotion(void)
{
	//if (!m_IsHiveMotherDead)
	//{
	//	m_tFrame.iFrameStart = 0;
	//	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	//	m_tFrame.iFrameEnd = 0;
	//	m_tFrame.iMotion = 0;
	//	m_tFrame.dwSpeed = 200;
	//	m_tFrame.dwTime = GetTickCount();
	//}
	//else
	//{
	//	m_tFrame.iFrameStart = 0;
	//	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	//	m_tFrame.iFrameEnd = 2;
	//	m_tFrame.iMotion = 0;
	//	m_tFrame.dwSpeed = 200;
	//	m_tFrame.dwTime = GetTickCount();
	//}
}

void CStatue_HiveMother::MoveFrame(void)
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = m_tFrame.iFrameEnd;

		m_tFrame.dwTime = GetTickCount();
	}
}
